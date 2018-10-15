#include <stdio.h>
#include <pigpio.h>

#define TX_PIN 22

int init() {
	int result;
	
	result = gpioInitialise();
	if (result != 0) {
		return result;
	}
	
	result = gpioSetMode(TX_PIN, PI_OUTPUT);
	if(result != 0) {
		return result;
	}
	
	return 0;
}

int transmit(int value) {
	return gpioWrite(TX_PIN, value);
}

void deinit() {
	gpioTerminate();
}
