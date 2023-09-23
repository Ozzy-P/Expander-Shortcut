// Obviously doesn't work, yet, or maybe ever.

/*
    TODO: [W] *Fix capitalization, somehow. Preferrably just capitalize the first letter then [REDACTED].
          [D] *Add copy and paste functionality from chatConverter.c
          [D] *Attempt to auto paste (probably not needed, esp if its a mist).
          [D] *Remove internet explorer.
*/

#include <windows.h>
#include <stdio.h>
#include "converter.h"

int Save(int _key, struct message *msgToSave, char *file);
char *hex = "#ffe000#ff0000#ffbb1e#5fff1e#8df9ea#8dacf9#5b16b9#b481fa#fa81eb#cd4040";
const int activator = 0x41;
const int copy = 0x42;

int main(void){
    int keyPressed = 0;

    struct message *currentMessage = createMessage();

    FreeConsole();
    while (1 == 1){
        Sleep(10);
        if ((GetAsyncKeyState(activator) & 0x8000) && !keyPressed){
            keyPressed = 1;
        }
        else if (!(GetAsyncKeyState(activator)) && keyPressed){
            keyPressed = 0;
            Save(activator, currentMessage, "log.txt");
        }
    }
    free(currentMessage);
    return 0;
}

int Save(int _key, struct message *msgToSave, char *file){
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    fprintf(OUTPUT_FILE, "START\n");
    int activeKey = 1;
    int pressedChars[255+8];

    int numberChars = 0;

    for(int iteration = 0; iteration < 255+8; iteration++){
        pressedChars[iteration] = 0;
    }

    while ((activeKey == 1)){
        Sleep(10);
        for (int i = 8; i < 255; i++){
            int keyState = GetAsyncKeyState(i);
            if((numberChars > MAX_CHARS) || ((keyState & 0x8000) && (i == copy))){
                activeKey = 0; 
                fprintf(OUTPUT_FILE, "%s\n", (msgToSave)->msg);
                formatToHex(msgToSave, hex);
                fprintf(OUTPUT_FILE, "'%s' with size %d\n", (msgToSave)->msg, (msgToSave)->currentCharCount);
                fclose(OUTPUT_FILE);
                copyMessage(msgToSave);
                clearArray(msgToSave);
                break;
            }
            if (!(keyState) && (pressedChars[i] == 1)){
                (msgToSave)->msg[numberChars] = i;
                numberChars++;
                pressedChars[i] = 0;
            }
            if ((keyState & 0x8000) && (pressedChars[i] == 0)){
                pressedChars[i] = 1;
            }
        }
    }
    return 0;
}
