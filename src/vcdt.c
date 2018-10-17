/*
 * Main module for vcd transmitter
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
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "driver.h"

static drivert* currentDriver;
static int lastTimestamp = 0;

static void printHelp() {
	printf("Usage: vcdt file_name -S signal_identifier -D driver_id\n");
	printf("Available drivers:\n\n");
	int i;
	drivert** drivers = getDrivers();
	
	for(i=0; i<getDriverCount(); i++) {
		drivert* d = drivers[i];
		printf("%d\t", d->id);
		printf("%s\t", d->name);
		printf("%s\n", d->description);
	}
}

static void gap(long time) {
	struct timespec tim1, tim2;
	tim1.tv_sec  = 0;
	tim1.tv_nsec = (time - lastTimestamp)*1000;
	
	nanosleep(&tim1, &tim2);
	lastTimestamp = time;
}

static int transmit(long time, int value) {
	gap(time);
	return currentDriver->transmit(value);
}

static char* getFileName(int argc, char **argv) {
	return argv[1];
}

static char getSignalIdentifier(int argc, char **argv) {
	for(int i=0; i < argc; i++) {
		if(strcmp(argv[i], "-S") == 0) {
			return argv[i+1][0];
		}
	}
}

static void setCurrentDriver(int argc, char **argv) {
	for(int i=0; i < argc; i++) {
		if(strcmp(argv[i], "-D") == 0) {
			currentDriver = getDriverById(atoi(argv[i+1]));
		}
	}
}

static int processArguments(int argc, char **argv) {
	setCurrentDriver(argc, argv);
	vct* parsed = parseVCDFile(getFileName(argc, argv), getSignalIdentifier(argc, argv));
	
	currentDriver->init();
	int result = handleResult(parsed, transmit);
	currentDriver->deinit();
	
	return result;
}

int main(int argc, char **argv) {
	if(argc < 6) {
		printHelp();
	}
	return processArguments(argc, argv);
}
