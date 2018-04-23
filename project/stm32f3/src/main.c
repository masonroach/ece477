#include "stm32f3xx.h"
#include "usart.h"
#include "led.h"
#include "button.h"

void systemInit(void);
void testSdSendByte(uint8_t byte);
void checkCRC(void);

int main(void) {
	uint8_t i = 0;
	uint8_t crc, crcH, crcL;

	systemInit();

	while (1) {
		while (readButton() == 0);	// Wait while button is not pushed
		if (++i > 8) i = 0;
		ledCircle(i);
		while (readButton() == 1);	// Wait while button is pushed
		usartSendChar('0' + readButton());
	}

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
	usartSendString("Initialized. Press button to continue.\r\n");
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
