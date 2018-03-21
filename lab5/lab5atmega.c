#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 2000000UL
#include <util/delay.h>

void serialInit(void);
void sendString(char *buffer);
unsigned char getGuess(void);
char getChar(void);
void putChar(char c);

int main(void)
{
	unsigned char num;
	unsigned char userGuess = 0;
	serialInit(); // Initialize serial communication on ATMega88	
	_delay_ms(50);
	
	sendString("Enter 0 to begin.\n\r");	
	// Infinite loop
	while (1) {
		// Wait for correct game start character
		while(getGuess() != 0);
		// Random number between 0-255
		num = rand() % 256;
		do {
			sendString("Enter your guess:\n\r");
			userGuess = getGuess();
			if (userGuess < num) sendString("LOW\n\r");
			if (userGuess > num) sendString("HIGH\n\r");
		} while (num != userGuess);
		sendString("CORRECT! Enter \"255\" to play again.\n\r");
	}
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
		if ((guess[i] < 48) || (guess[i] > 57)) {
			// add null terminator and convert to char
			guess[i] = '\0';
			break;
		}
		i++;
	}
	i = atoi(guess);
	if (i>255) i = 255;
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
