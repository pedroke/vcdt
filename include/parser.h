#ifndef PARSER_H
#define PARSER_H

typedef struct vc {
    long time;
    int value;
    struct vc* next;
} vct;

vct* parseVCDFile(char* fileName, char signalIdentifier);

int handleResult(vct* resultList, int (*callback)(long, int));

#endif
