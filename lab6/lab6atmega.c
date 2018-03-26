#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 20000000UL
#include <util/delay.h>

void serialInit(void);
void sendString(char *buffer);
char getChar(void);
void putChar(char c);
void my_delay_ms(int ms);
void tempInit(void);
int tempGet(void);

int main(void)
{
	serialInit(); // Initialize serial communication on ATMega88	
		
	return 0;
}


void serialInit(void)
{
	UBRR0H = 0;
	// Initializes AVR USART for 9600 baud (assuming 2MHz clock)
	// 2MHz/(16*(6+1)) = 9615
	UBRR0L = 6; // Set baud rate to 9600 for 2 MHz clock
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable TX and RX, 8 bit
	UCSR0C |= (3<<UCSZ00); // 8 bit communication
	UCSR0C &= ~(3<<UPM00); // no parity 
	UCSR0C &= ~(1<<USBS0); // 1 stop bit
}


void tempInit(void)
{
	ADMUX = 0x00;		// Clear all bits in ADMUX register (0x7C)
	ADMUX |= 0x08;		// Select temp sensor channel. ADMUX.MUX[3:0] = 0b1000
	ADMUX |= 0xC0;		// Select 1.1V internal ref voltage. ADMUX.REFS[1:0] = 0b11

	ADCSRA |= 0x80;		// Turn on ADC. ADCSRA.ADEN = 0b1
	ADCSRA |= 0x06;		// Timer offset factor of 64. ADCSRA.ADPS[2:0] = 0b110
}


int tempGet(void) {
	int temp;
	char high, low;

	ADCSRA |= 0x40;		// Start conversion. ADCSRA.ADSC = 0b1
	while (ADCSRA & 0x40);	// Wait for ADCSRA.ADSC bit to be set to 0
	low = ADCL;		// Get low 8 bits of ADC
	high = ADCH;		// Get high 2 bits of ADC
	temp = (high << 8) | low;	// Convert to a temperature

	return (temp - 289);	// Convert reading to C
}


void sendString(char *buffer)
{
	int i;
	for(i=0; i<strlen(buffer); i++){
		putChar(buffer[i]);
	}
}


unsigned char getGuess(void)
{
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

char getChar(void)
{
	// wait for empty receiving buffer
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}

void putChar(char c)
{
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
