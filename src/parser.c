#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


char* getValue(char* line, int index, char* result) {
	int i = 0;
	
	while(line[index] != ' ') {
		result[i++] = line[index--];
	}
	
	return result;
}

vct* parseLine(char* line, char signalIdentifier) {
	char c = line[0];
	char time[12];
	char value[12];
	int timeIndex = 0;
	int lineIndex = 0;
	vct* result;

 	if(c == '#') {
		do {
			if(c == signalIdentifier) {
				result = malloc(sizeof(vct));
				result->time = strtol(time, NULL, 10);
				result->value = atoi(getValue(line, lineIndex-1, value));
				result->next = NULL;
				
				return result;
			}
			c = line[++lineIndex];
			if(timeIndex != -1) {
				if(c != ' ') {
					time[timeIndex++] = c;
				} else {
					time[timeIndex] = '\0';
					timeIndex = -1;
				}
			}
		} while(c!='\0');
	}
	
	return NULL;
}

FILE* openFile(char* fileName) {
	FILE *fp;
	fp = fopen(fileName, "r");
	
	if (fp == NULL) {
      perror("Error opening the file.\n");
      exit(EXIT_FAILURE);
    }
	
	return fp;
}

int handleResult(vct* resultList, int (*callback)(long, int)) {
	vct* purge;
	int result = 0;
	
	while(resultList != NULL) {
		result = (*callback)(resultList->time, resultList->value);
		if(result != 0) {
			return result;
		}
		purge = resultList;
		resultList = resultList->next;
		free(purge);
	}
	
	return result;
}

vct* parseVCDFile(char* fileName, char signalIdentifier) {
	FILE *fp = openFile(fileName);
	char line[100];
	vct* resultList = NULL;
	vct* next = NULL;

	while ((fgets(line, sizeof(line), fp) != NULL) && (resultList == NULL)){
		next = parseLine(line, signalIdentifier);
        if(next != NULL) {
			resultList = next;
		}
	}
	
	while (fgets(line, sizeof(line), fp) != NULL){
        next->next = parseLine(line, signalIdentifier);
        if(next->next != NULL) {
			next = next->next;
		}
		
    }
	
	fclose(fp);
	
	return resultList;
}
