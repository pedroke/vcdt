/*
 * Transmitter driver for raspberry pi utilizing pigpio library to
 * transmit to cheap OOK transmitter connected to RPi I/O ports.
 * 
 * 
 * Copyright (C) 2018 by Peter Drozda
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <pigpio.h>
#include "driver.h"

#define TX_PIN 22

static int init() {
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

static int transmit(int value) {
	return gpioWrite(TX_PIN, value);
}

static void deinit() {
	gpioTerminate();
}

drivert rpiook = {
	.id = 1,
	.name = "rpiook",
	.description = "Driver for raspberry pi utilizing pigpio library to transmit to cheap OOK transmitter",
	.init = init,
	.deinit = deinit,
	.transmit = transmit
};
