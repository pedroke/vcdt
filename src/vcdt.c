#include <stdio.h>
#include <unistd.h>
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
	sleep(time - lastTimestamp);
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
			getDriverById(atoi(argv[i+1]));
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
