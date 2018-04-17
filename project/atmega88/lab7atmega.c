#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define BAUD 1200
#define MYUBRR ((F_CPU/16)/BAUD - 1)

#define DELAY_SEC 1	// 1 min delay

void serialInit(void);
void sendString(char *buffer);
char getChar(void);
void putChar(unsigned char c);
void my_delay_ms(int ms);
void my_delay_sec(int sec);
void tempInit(void);
int tempGet(void);
void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);
void blinkError(int errnum);

int main(void) {
	char csvRow[256] = {0};
	unsigned char i2cData[8] = {0};
	int avrTemp = 0;
	unsigned int sec = 0, min = 0, hr = 0;

	ledInit();	// Initialize the LED
	serialInit();	// Initialize serial communication on ATMega88
	tempInit();	// Initialize the internal temp sensor

	ledOff();	// Turn off the LED. Will be turned back on in the while loop
	blinkError(3);

	while (1) {
		avrTemp = tempGet();
		sprintf(csvRow, "%d, %d, %02d:%02d:%02d\r\n", avrTemp, i2cData[0], hr, min, sec);
		sendString(csvRow);
		ledToggle();
		my_delay_sec(DELAY_SEC);
	
		// Increment the time
		sec += (DELAY_SEC);
		if (sec / 60) {		// If seconds rolls over
			min += sec/60;	// Carry to minutes
			sec %= 60;
		}
		if (min / 60) {		// If mins rolls over
			hr += min/60;	// Carry to hours
			min %= 60;
		}
	}

	return 0;
}

void serialInit(void) {
	UBRR0H = (unsigned char) (MYUBRR >> 8);
	UBRR0L = (unsigned char) (MYUBRR); // Set baud rate to 9600 for 2 MHz clock
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0); // Enable TX and RX, 8 bit
	UCSR0C = 0x00;			// Clear all bits in UCSR0C
	UCSR0C |= (0<<UMSEL00);		// Asynchronous
	UCSR0C |= (0<<UPM00);		// No Parity
	UCSR0C |= (0<<USBS0);		// 1 Stop bit
	UCSR0C |= (3<<UCSZ00);		// 8-bit Data
}

void tempInit(void) {

	ADMUX |= (1 << REFS1) | (1 << REFS0);		// Select 1.1V internal ref voltage. ADMUX.REFS[1:0] = 0b11
	ADMUX |= (1 << MUX3);				// Select Temperature sensor channel

	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);	// Select temp sensor channel. ADMUX.MUX[3:0] = 0b1000

}

int tempGet(void) {
	int temp;
	int high, low;
	long ADC_read;

	ADCSRA |= (1 << ADSC);		// Start conversion. ADCSRA.ADSC = 0b1
	while (ADCSRA & (1 << ADSC));	// Wait for ADCSRA.ADSC bit to be set to 0
	low = ADCL;
	high = ADCH;
	ADC_read = (high << 8) | low;	// Convert to a temperature

	temp = (ADC_read * 1000 * 1.1) / 1024;

	return (temp - 289);	// Convert reading to C
}

void sendString(char *buffer) {
	int i;
	for(i=0; i<strlen(buffer); i++){
		putChar(buffer[i]);
	}
}

unsigned char getGuess(void) {
	char guess[50];
	unsigned int i = 0;
	while(1){
		// store input
		guess[i] = getChar();
		// if user enters a non-numerical character
		if ((guess[i] < '0') || (guess[i] > '9')) {
			// add null terminator and convert to char
			guess[i] = '\0';
			break;
		}
		i++;
	}
	i = atoi(guess);
	if (i>255) i = 255;
	if (i == 0) PORTB |= 0x01;
	return (unsigned char)i;
}

char getChar(void) {
	// wait for empty receiving buffer
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}

void putChar(unsigned char c) {
	// wait for empty transmission buffer
	while((UCSR0A&(1<<UDRE0)) == 0);
	UDR0 = c;
}

void my_delay_ms(int ms) {
	while (ms > 0) {
		_delay_ms(1);
		--ms;
	}
}

void my_delay_sec(int sec) {
	while (sec > 0) {
		_delay_ms(1000);
		--sec;
	}
}

void ledInit() {
	DDRB |= 0x01;
	DDRB &= ~0x02;
}

void ledOn() {
	PORTB |= 0x01;
}

void ledOff() {
	PORTB &= ~(0x01);
}

void ledToggle() {
	PORTB ^= 0x01;
}

void blinkError(int errnum) {
	while (errnum > 0) {
		ledOn();
		_delay_ms(100);
		ledOff();
		_delay_ms(100);
		--errnum;
	}
}
