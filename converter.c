#include <windows.h>
#include <stdio.h>
#include "converter.h"

const int MAX_CHARS = 50;

void formatToHexStatic(struct message *msgToCopy, char *hexValues){
    char tempArray[MAX_CHARS * 7];

    for(int i = 0; i < MAX_CHARS * 7; i++){
        tempArray[i] = 0;
    }
    
    int r = rand() % 10;
    strcat(tempArray,"(");
    strncat(tempArray,hexValues+(r*7),7);
    strcat(tempArray,"/");   
    strcat(tempArray,(msgToCopy)->msg);   
    strcat(tempArray,") ");  

    for(int i = 0; i < MAX_CHARS * 7; i++){
        if(tempArray[i] == '\0'){
            break;
        }
        (msgToCopy)->msg[i] = tempArray[i];
        (msgToCopy)->currentCharCount++;
    }
}

void formatToHex(struct message *msgToCopy, char *hexValues){
    char tempArray[MAX_CHARS * 7];

    for(int i = 0; i < MAX_CHARS * 7; i++){
        tempArray[i] = 0;
    }
    
    char *token = strtok((msgToCopy)->msg, " ");
    while(token != NULL) {
        int r = rand() % 10;
        strcat(tempArray,"(");
        strncat(tempArray,hexValues+(r*7),7);
        strcat(tempArray,"/");   
        strcat(tempArray,token);   
        strcat(tempArray,") ");  
        token = strtok(NULL, " ");
    }

    for(int i = 0; i < MAX_CHARS * 7; i++){
        if(tempArray[i] == '\0'){
            break;
        }
        (msgToCopy)->msg[i] = tempArray[i];
        (msgToCopy)->currentCharCount++;
    }
}

void clearArray(struct message *msgToClear){
    for(int i = 0; i < MAX_CHARS*7; i++){
        (msgToClear)->msg[i] = 0;
    }
    (msgToClear)->hMem = GlobalAlloc(GMEM_MOVEABLE, 7*MAX_CHARS);
    (msgToClear)->currentCharCount = 0;
}

struct message *createMessage(){
    struct message *currentMessage = (struct message *) malloc(sizeof(struct message));
    (currentMessage)->hMem = GlobalAlloc(GMEM_MOVEABLE, 7*MAX_CHARS);
    (currentMessage)->currentCharCount = 0;
    char newArray[MAX_CHARS * 7];
    for(int i = 0; i < MAX_CHARS * 7; i++){
        newArray[i] = 0;
    }
    (currentMessage)->msg = newArray;
    return currentMessage;
}

void copyMessage(struct message *msgToCopy){
    memcpy(GlobalLock((msgToCopy)->hMem), (msgToCopy)->msg, (msgToCopy)->currentCharCount);
    GlobalUnlock((msgToCopy)->hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, (msgToCopy)->hMem);
    CloseClipboard();
}

void saveToFile(int msgSize, char *msg[msgSize], char *file){
    FILE *OUTPUT_FILE = fopen(file, "a+");
    for(int i = 0; i < msgSize; i++){
        int x = 0;
        while(msg[i][x] != '\0'){
            fprintf(OUTPUT_FILE,"%c",msg[i][x]);
            x++;
        }
    }
    fprintf(OUTPUT_FILE, "\n");
    fclose(OUTPUT_FILE);
}
