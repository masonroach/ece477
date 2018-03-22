#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 2000000UL
#include <util/delay.h>
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

int morseDelay = 10;

void serialInit(void);
void sendString(char *buffer);
unsigned char getGuess(void);
char getChar(void);
void putChar(char c);
void morseInit(int ms);
void morseMessage(char *msg);

int main(void)
{
	char *morseMsg = "Correct";
	unsigned char num;
	unsigned char userGuess = 0;
	serialInit(); // Initialize serial communication on ATMega88	
	morseInit(30); // Initialize morse code blinker with ms time unit
	morseMessage("Welcome to the serial high/low game");
		
	sendString("Enter 0 to begin");	
	// Infinite loop
	while (1) {
		// Wait for correct game start character
		while(getGuess() != 0);
		// Random number between 0-255
		num = rand() % 256;
		do {
			sendString("Enter your guess");
			userGuess = getGuess();
			if (userGuess < num) sendString("L");
			if (userGuess > num) sendString("H");
		} while (num != userGuess);
		sendString("C");

		// Blink morse message on LED before beginning new game
		sprintf(morseMsg, "The correct number was %d", num);
		morseMessage(morseMsg);
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

void morseInit(int ms)
{
	// ms is number of milliseconds for morse unit
	morseDelay = ms;
	DDRB |= 0x01; // set PB0 output
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
				_delay_ms(morseDelay); // dot, 1 time unit
				PORTB &= ~(0x01); // LED off
				_delay_ms(morseDelay);
			} else {
				PORTB |= 0x01; // LED on
                                _delay_ms(3 * morseDelay); // dash, 3 time units
                                PORTB &= ~(0x01); // LED off
                                _delay_ms(morseDelay);
			}
		}

		// if space or invalid char, blink space
		if (tableIndex == -1) {
			_delay_ms(4*morseDelay); // low 7 time units
			// Only 4 to account for 3 below
		}

		// space between letters is 3 time units
		_delay_ms(3*morseDelay);
	}
}
