#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define BAUD 1200
#define MYUBRR ((F_CPU/16)/BAUD - 1)

void serialInit(void);
void sendString(char *buffer);
unsigned char getGuess(void);
char getChar(void);
void putChar(unsigned char c);
void my_delay_ms(int ms);
void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);

int main(void)
{
	unsigned char num;
	unsigned char state = 0;
	unsigned char testString[100];

	for (num = 0; num < sizeof(testString)/sizeof(testString[0]); num++) testString[num] = num + 1;
	testString[sizeof(testString)/sizeof(testString[0]) - 1] = '\0';

	serialInit(); // Initialize serial communication on ATMega88	
	ledInit();	// testing stuff
	ledOn();

	sendString("Enter 0 to begin");	
	_delay_ms(500);
	sendString("Test\n");
	while (1) {
	sendString("Test2\n\r");
	_delay_ms(500);
}

	return 0;
}


void serialInit(void)
{
	UBRR0H = (unsigned char) (MYUBRR >> 8);
	UBRR0L = (unsigned char) (MYUBRR); // Set baud rate to 9600 for 2 MHz clock
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0); // Enable TX and RX, 8 bit
	UCSR0C = 0x00;			// Clear all bits in UCSR0C
	UCSR0C |= (0<<UMSEL00);		// Asynchronous
	UCSR0C |= (0<<UPM00);		// No Parity
	UCSR0C |= (0<<USBS0);		// 1 Stop bit
	UCSR0C |= (3<<UCSZ00);		// 8-bit Data
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

void putChar(unsigned char c)
{
	// wait for empty transmission buffer
	while( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = c;
}

void my_delay_ms(int ms) {
	while (ms > 0) {
		_delay_ms(1);
		--ms;
	}
}

void ledInit()
{
	DDRB |= 0x01;
	DDRB &= ~0x02;
}

void ledOn()
{
	PORTB |= 0x01;
}

void ledOff()
{
	PORTB &= ~(0x01);
}

void ledToggle()
{
	PORTB ^= 0x01;
}
