/*
 * Dummy transmitter driver intended as template and for testing purposes
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
#include "driver.h"

static int init() {
	printf("Initialization of dummy driver.\n");
	return 0;
}

static int transmit(int value) {
	printf("Dummy transmit: %d\n", value);
	return 0;
}

static void deinit() {
	printf("Deinitialization of dummy driver.\n");	
}

drivert dummy = {
	.id = 2,
	.name = "dummy",
	.init = init,
	.deinit = deinit,
	.transmit = transmit
};
