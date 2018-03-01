#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 2000000UL
#include <util/delay.h>


int main(void)
{
	unsigned int delay = 200;
	int i = 0, j = 0;

	DDRB |= 0x01; // set PB0 output
	DDRB &= ~0x02; // PB1 input
	PORTB |= 0x02; // PB1 pullup enabled

	// Infinite loop
	while (1) {
		if (!(PINB & 0x02)) { // If button is pushed
			i++;
			for (i %= 50, j = 0; j < i; j++) _delay_us(1);
			PORTB ^= 0x01; // Toggle LED
			for (j = 0; j < 50 - i; j++) _delay_us(1);
			PORTB ^= 0x01; // Toggle LED
		} else {
			_delay_ms(200);
			PORTB ^= 0x01; // Toggle LED
		}
	}
}
