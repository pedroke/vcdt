#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "driver.h"

static drivert* currentDriver;

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

int transmit(long time, int value) {
	int result = currentDriver->transmit(value);
	sleep(time);
	return result;
}

int processArguments(int argc, char **argv) {
	char* fileName; // TODO
	char signalIdentifier; //TODO
	
	vct* parsed = parseVCDFile(fileName, signalIdentifier);
	return handleResult(parsed, transmit);
}

int main(int argc, char **argv) {
	if(argc < 6) {
		printHelp();
	}
	return processArguments(argc, argv);
}
