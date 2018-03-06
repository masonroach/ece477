#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 2000000UL
#include <util/delay.h>

void serialInit(void);


int main(void)
{
	serialInit(); // Initialize serial communication on ATMega88	

	// Infinite loop
	while (1) {
	}
}


void serialInit(void)
{
	UBRRH = 0;
	// Initializes AVR USART for 4800 baud (assuming 1MHz clock)
	// 2MHz/(16*(12+1)) = 9615
	UBRRL = 12; // Set baud rate to 9600 for 2 MHz clock

	// TODO: Change to 1 stop bit in statement below
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0); // 8 bit 2 stop bit no parity
	UCSRB = (1<<RXEN)|(1<<TXEN); // Enable TX and RX, 8 bit
}
