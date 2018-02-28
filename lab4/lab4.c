#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	unsigned int delay = 200;

	DDRB |= 0x01; // set PC0 output
	DDRB &= ~0x02; // PC1 input
	PORTB |= 0x02; // PB1 pullup enabled

	// Infinite loop
	while (1) {
		PORTB ^= 0x01; // Toggle LED
		_delay_ms(delay); // delay

		if (!(PINB &= 0x02)) { // If button is pushed
			delay = 20; // STROBE
		} else {
			delay = 200; // normal
		}
	}
}
