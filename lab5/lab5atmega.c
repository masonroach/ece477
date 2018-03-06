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
	UBRRL = 12; // Set baud rate for 2 MHz clock
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	UCSRB = (1<<RXEN)|(1<<TXEN);
}
