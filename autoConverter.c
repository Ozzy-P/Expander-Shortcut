// Obviously doesn't work, yet, or maybe ever.

/*
    TODO: [W] *Fix capitalization, somehow. Preferrably just capitalize the first letter then [REDACTED].
          [D] *Add copy and paste functionality from chatConverter.c
          [D] *Attempt to auto paste (probably not needed, esp if its a mist).
          [W] *Remove internet explorer.
*/

#include <windows.h>
#include <stdio.h>
#include "converter.h"

int Save(int _key, struct message *msgToSave, char *file);
char *hex = "#ffe000#ff0000#ffbb1e#5fff1e#8df9ea#8dacf9#5b16b9#b481fa#fa81eb#cd4040";

int main(void){
    int keyPressed = 0;
    int keyBind = 0x41;

    struct message *currentMessage = (struct message *) malloc(sizeof(struct message));

    FreeConsole();
    while (1 == 1){
        Sleep(10);
        if ((GetAsyncKeyState(keyBind) & 0x8000) && !keyPressed){
            keyPressed = 1;
        }
        else if (!(GetAsyncKeyState(keyBind)) && keyPressed){
            keyPressed = 0;
            Save(keyBind, currentMessage, "log.txt");
        }
    }
    free(currentMessage);
    return 0;
}

int Save(int _key, struct message *msgToSave, char *file){
    Sleep(10);
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, 7*MAX_CHARS);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    fprintf(OUTPUT_FILE, "START\n");
    int activeKey = 1;
    int pressedChars[255+8];

    char allocConvert[MAX_CHARS * 7 + 1];
    int numberChars = 0;

    for(int iteration = 0; iteration < 255+8; iteration++){
        pressedChars[iteration] = 0;
    }

    for(int iteration = 0; iteration < sizeof(allocConvert); iteration++){
        allocConvert[iteration] = 0;
    }

    while ((activeKey == 1)){
        Sleep(10);
        for (int i = 8; i < 255; i++){
            if((numberChars > MAX_CHARS)){
                activeKey = 0; 
                break;
            }
            int keyState = GetAsyncKeyState(i);
            if ((keyState & 0x8000) && (i == 0x42)){
                activeKey = 0;
                fprintf(OUTPUT_FILE, "END\n");
                fclose(OUTPUT_FILE);

                formatToHex(allocConvert, msgToSave, hex);
                copyMessage(hMem,allocConvert, sizeof(allocConvert) / sizeof(allocConvert[0]));
                clearArray(msgToSave);
                break;
            }
            if (!(keyState) && (pressedChars[i] == 1)){
                fprintf(OUTPUT_FILE, "%s", &i);
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
