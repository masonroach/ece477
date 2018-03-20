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

int main(void)
{
	unsigned char num;
	unsigned char userGuess = 0;
	serialInit(); // Initialize serial communication on ATMega88	
	
	// Infinite loop
	while (1) {
		// Wait for correct game start character
		while(getGuess() != 255);
		// Random number between 0-255
		num = rand() % 256;
		do {
			sendString("Enter your guess: ");
			userGuess = getGuess();
			if (userGuess < num) sendString("LOW");
			if (userGuess > num) sendString("HIGH");
		} while (num != userGuess);
		sendString("CORRECT! Enter \"255\" to play again.");
	}
	return 0;
}


void serialInit(void)
{
	UBRR0H = 0;
	// Initializes AVR USART for 4800 baud (assuming 1MHz clock)
	// 2MHz/(16*(12+1)) = 9615
	UBRR0L = 12; // Set baud rate to 9600 for 2 MHz clock
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable TX and RX, 8 bit
	// Lab assignment specifies 1 stop bit, but according to
	// datasheet, for 8 bit communication 2 stop bits are
	// REQUIRED
	UCSR0C = ((1<<USBS0)|(3<<UCSZ00)); // 8 bit 2 stop bit no parity
	UCSR0C &= ~(3<<UPM00);
}



void sendString(char *buffer)
{
	int i;
	for(i=0; i<strlen(buffer); i++){
		// Wait for buffer to empty then write new char
		while((UCSR0A&(1<<UDRE0)) == 0);
		UDR0 = buffer[i];
	}
}


unsigned char getGuess(void)
{
	char guess[50];
	unsigned int i = 0;
	while(i<50){
		// Wait for input
		while(!(UCSR0A&(1<<RXC0)));
		// store input
		guess[i] = UDR0;
		// if user presses enter key
		if (guess[i] == '\n' || guess[i] == '\r') {
			// add null terminator and convert to char
			guess[i+1] = '\0';
			return (unsigned char)atoi(guess);
		}
	}
	return 0;
}
