#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define BAUD 4800
#define MYUBRR ((F_CPU/16)/BAUD - 1)

#define DELAY_SEC 1	// 1 min delay

#define MESSLEN 64	// 64 char message

void serialInit(void);
void sendString(char *buffer);
char getChar(void);
void getStr(char *str, int length);
void putChar(unsigned char c);
void my_delay_ms(int ms);
void my_delay_sec(int sec);
void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);
void blinkError(int errnum);
void morseMessage(char *msg);
int checkCRC(char *msg, int length, unsigned char crc);

			 //  A      B        C      D     E     F
const char* morseDecode[36] = {".-", "-...", "-.-.", "-..", ".", "..-.", 
			 //   G      H       I     J       K      L
			    "--.", "....", "..", ".---", "_._", ".-..", 
			//    M     N     O      P       Q       R      S
			    "--", "-.", "---", ".--.", "--.-", ".-.", "...",
			//   T     U      V       W       X      Y       Z
 			    "-", "..-", "...-", ".--", "-..-", "-.--", "--..", 
			// 0         1       2        3        4        5 
			"-----", ".----", "..---", "...--", "....-", ".....",
			// 6        7        8        9
			"-....", "--...", "---..", "----."};

int morseDelay = 20;


int main(void) {
	char msg[MESSLEN];
	unsigned char crc;

	ledInit();	// Initialize the LED
	serialInit();	// Initialize serial communication on ATMega88
	ledOff();	// Turn off the LED. Will be turned back on in the while loop

	while (1) {
		// Get input
		getStr(msg, MESSLEN);

		// Get CRC byte and remove it from string
		crc = msg[MESSLEN-1];
		msg[MESSLEN-1] = '\0';

		// Echo input to verify
		sendString(msg);
		sendString("\r\n");

		// Check CRC for correctness
		if (checkCRC(msg, MESSLEN-1, crc)){
			// Blink message for correct CRC
			morseMessage(msg);
		} else {
			// Blink 3 error flashes for incorrect CRC
			blinkError(3);
		}
	
	}

	return 0;
}

void serialInit(void) {
	UBRR0H = (unsigned char) (MYUBRR >> 8);
	UBRR0L = (unsigned char) (MYUBRR); // Set baud rate to 9600 for 2 MHz clock
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0); // Enable TX and RX, 8 bit
	UCSR0C = 0x00;			// Clear all bits in UCSR0C
	UCSR0C |= (0<<UMSEL00);		// Asynchronous
	UCSR0C |= (0<<UPM00);		// No Parity
	UCSR0C |= (0<<USBS0);		// 1 Stop bit
	UCSR0C |= (3<<UCSZ00);		// 8-bit Data
}

void sendString(char *buffer) {
	int i;
	for(i=0; i<strlen(buffer); i++){
		putChar(buffer[i]);
	}
}

void getStr(char* str, int l) {
	int i;
	for (i=0; i<l; i++) {
		str[i] = getChar();
	}
}

char getChar(void) {
	// wait for empty receiving buffer
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}

void putChar(unsigned char c) {
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

void my_delay_sec(int sec) {
	while (sec > 0) {
		_delay_ms(1000);
		--sec;
	}
}

void ledInit() {
	DDRB |= 0x01;
	DDRB &= ~0x02;
}

void ledOn() {
	PORTB |= 0x01;
}

void ledOff() {
	PORTB &= ~(0x01);
}

void ledToggle() {
	PORTB ^= 0x01;
}

void blinkError(int errnum) {
	while (errnum > 0) {
		ledOn();
		_delay_ms(100);
		ledOff();
		_delay_ms(100);
		--errnum;
	}
}

void morseMessage(char *msg)
{
	// Blinks msg in morse code after win
	// Valid chars are alphabet and numbers
	// otherwise, interpret as space

	int i, j, tableIndex = 0;
	// for each char in string
	for (i=0;i<strlen(msg);i++){
		// select char
		if (msg[i] >= 'a' && msg[i] <= 'z') {
			// lowercase letters
			tableIndex = msg[i] - 'a';
		} else if (msg[i] >= 'A' && msg[i] <= 'Z') {
			// uppercase letters
			tableIndex = msg[i] - 'A';
		} else if (msg[i] >= '0' && msg[i] <= '9') {
			// numbers come after spaces in lookup table
			tableIndex = msg[i] - '0' + 26;
		} else {
			tableIndex = -1; // print space
		}
		
		// blink char
		for (j=0; tableIndex>0 && j<strlen(morseDecode[tableIndex]); j++){
			if (morseDecode[tableIndex][j] == '.'){
				PORTB |= 0x01; // LED on
				my_delay_ms(morseDelay); // dot, 1 time unit
				PORTB &= ~(0x01); // LED off
				my_delay_ms(morseDelay);
			} else {
				PORTB |= 0x01; // LED on
                                my_delay_ms(3 * morseDelay); // dash, 3 time units
                                PORTB &= ~(0x01); // LED off
                                my_delay_ms(morseDelay);
			}
		}

		// if space or invalid char, blink space
		if (tableIndex == -1) {
			my_delay_ms(4*morseDelay); // low 7 time units
			// Only 4 to account for 3 below
		}

		// space between letters is 3 time units
		my_delay_ms(3*morseDelay);
	}
}


int checkCRC(char *msg, int length, unsigned char crc)
{
	int j;
	for(j=0;j<length;j++);
	return 1;
}
