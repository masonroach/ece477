#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	DDRB |= 0x01; // set PORTC pin 5 as output
	while(1){
		PORTB ^= 0x01; // Toggle LED
		_delay_ms(200);
	}
}
