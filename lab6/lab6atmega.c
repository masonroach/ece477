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
