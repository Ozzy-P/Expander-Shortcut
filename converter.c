#include <windows.h>
#include <stdio.h>
#include "converter.h"

const int MAX_CHARS = 50;

void formatToHex(char *targetArray, struct message *msgToCopy, char *hexValues){
    char *token = strtok((msgToCopy)->msg, " ");
    while(token != NULL) {
        int r = rand() % 10;
        strcat(targetArray,"(");
        strncat(targetArray,hexValues+(r*7),7);
        strcat(targetArray,"/");   
        strcat(targetArray,token);   
        strcat(targetArray,") ");  
        token = strtok(NULL, " ");
    }
}

void clearArray(struct message *msgToClear){
    for(int i = 0; i < MAX_CHARS; i++){
        (msgToClear)->msg[0] = 0;
    }
}

void copyMessage(HGLOBAL hMem, char *msgToCopy, int size){
    memcpy(GlobalLock(hMem), msgToCopy, size);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    GlobalFree(hMem);
}
