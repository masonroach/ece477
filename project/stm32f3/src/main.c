#include "stm32f3xx.h"
#include "usart.h"
#include "led.h"
#include "button.h"

void systemInit(void);
void sendMorseString(uint8_t *str);
uint8_t getCRC(char *msg, int length);

const unsigned char CRC7_POLY = 0x91;

int main(void) {
	uint8_t i = 0;
	uint8_t crc, crcH, crcL;
	uint8_t c = 'A';

	systemInit();

	sendMorseString("Patrick why doesnt this workkkkkk");

	return 1;
}

void systemInit(void) {
	int8_t i = 0;
	volatile uint16_t j = 0;

	initLeds();
	usartConfig();
	initButton();	
	
	/*
	 * Initialization is complete. User can press the button to continue at
	 * any time. Until then, a single serial message will be sent, and the
	 * LEDs will continue to light up in a circle.
	 */
	while (readButton() == 0) {
		if (++i > 15) i = 0;
		if (i <= 8) {
			ledCircle(i);
		} else {
			ledCircleInverted(i%8);
		}
		for (j = 0; j < 50000; j++);
	}
	ledAllOff();
}

void sendMorseString(uint8_t *str) {
	uint8_t strToSend[64];
	uint16_t i = 0;	

	while (str[i] != '\0') {
		strToSend[i] = str[i];
		i++;
	}
	while (i < 63) {
		strToSend[i] = 0;
		i++;
	}

	strToSend[63] = getCRC(strToSend, 63);

	for (i = 0; i < 64; i++) usartSendChar(strToSend[i]);
}

uint8_t getCRC(char *msg, int length) {
	unsigned char i, j, crc = 0;

	// Calculate CRC
	for (i = 0; i < length; i++){
		crc ^= msg[i];
    		for (j = 0; j < 8; j++){
      			if (crc & 1) crc ^= CRC7_POLY;
      			crc >>= 1;
		}
	}

	return crc;
}
