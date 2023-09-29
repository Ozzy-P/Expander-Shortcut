/*

    What is this monster? 
    Just an ordinary chat color coder for BetterChat v3.

    TODO: [D] *Fix capitalization, somehow. Preferrably just capitalize the first letter then [REDACTED].
          [D] *Add copy and paste functionality from chatConverter.c
          [D] *Attempt to auto paste (probably not needed, esp if its a mist).
          [D] *Remove internet explorer.
          [D] *Add keybind to change mode to a static color (toggle console to input change).
          [D] Fix write operation from copying and pasting invalid characters based on input (literally any non-alphabetic character).
          [W] Add support for shift -> special keys [!@#$%^&*().,], caps lock. And obvs, special keys.
          [D] Shift capitalization to this file (e.g. handle a shift key in succession with a letter [maybe even caps lock]).
          * Side note: May become too messy having it directly near a main method. [NC]
          [W] Fix copy and paste operation leaving remnants from old operations (possibly still reading from alloc'd garbage addresses?).
          [D] Shift logging to converter file, also figure out how to send an array of arrays without a static size.
*/

#include <windows.h>
#include <stdio.h>
#include "converter.h"

int Save(int _key, struct message *msgToSave, char *file, int textMode);
int isAlphabeticalKey(int key);
char *hex = "#ffe000#ff0000#ffbb1e#5fff1e#8df9ea#8dacf9#5b16b9#b481fa#fa81eb#cd4040";
const int activator = VK_OEM_2;
const int copy = VK_OEM_6;
const int exitKey = VK_OEM_5;
const int editSettings = VK_OEM_3;
//const int cancelKey = VK_OEM_4;

int main(void){
    int keyPressed = 0;
    int interruptPressed = 0;
    int mode = 0;

    struct message *currentMessage = createMessage();

    FreeConsole();
    while (1 == 1){
        Sleep(10);
        if ((GetAsyncKeyState(exitKey) & 0x8000)){
            break;
        }
        if ((GetAsyncKeyState(editSettings) & 0x8000) && !interruptPressed){
            interruptPressed = 1;
        }
        else if (!(GetAsyncKeyState(editSettings)) && interruptPressed){
            interruptPressed = 0;
            AllocConsole();
            freopen_s((FILE**)stdout, "CONIN$", "r", stdin);
            freopen_s((FILE**)stdout, "CONOUT$", "w", stderr);
            freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
            printf("Enter mode:");
            scanf("%d",&mode);
            printf("%d",mode);
            //fclose((FILE*)stdout);
            FreeConsole();
        }
        if ((GetAsyncKeyState(activator) & 0x8000) && !keyPressed){
            keyPressed = 1;
        }
        else if (!(GetAsyncKeyState(activator)) && keyPressed){
            keyPressed = 0;
            Save(activator, currentMessage, "log.txt", mode);
        }
    }
    free(currentMessage);
    return 0;
}

int Save(int _key, struct message *msgToSave, char *file, int textMode){
    saveToFile(1, (char *[1]){"LOG START"}, file);
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
            if(keyState & 0x8000){
                switch(i) {
                    case VK_OEM_4:
                    case VK_ESCAPE:
                    case VK_OEM_2:
                        activeKey = 0;
                        break;
                    default:
                        break;
                }
                if(!activeKey){
                    clearArray(msgToSave);
                    break;
                }
            }
            if ((numberChars > MAX_CHARS-2)){
                activeKey = 0; 
                clearArray(msgToSave);
                break;
            }
            if((keyState & 0x8000) && (i == copy)){
                activeKey = 0; 
                (msgToSave)->msg[MAX_CHARS-1] = '\0';
                if(!textMode){
                    formatToHexStatic(msgToSave,hex);
                }else{
                    formatToHex(msgToSave, hex);
                }
                saveToFile(2, (char *[2]){(msgToSave)->msg," was entered."}, file);
                copyMessage(msgToSave);
                clearArray(msgToSave);
                break;
            }
            if (!(keyState) && (pressedChars[i] == 1)){
                if((i == VK_BACK) && (numberChars > 0)){
                    (msgToSave)->msg[numberChars-1] = 0;
                    numberChars--; 
                }else if((i != VK_BACK) && isAlphabeticalKey(i)){
                    (msgToSave)->msg[numberChars] = ((msgToSave)->shiftActive) ? i : tolower(i);
                    numberChars++;
                }
                pressedChars[i] = 0;
                if(i == VK_SHIFT){
                    (msgToSave)->shiftActive = 0;
                }
            }
            if ((keyState & 0x8000) && (pressedChars[i] == 0)){
                pressedChars[i] = 1;
                if(i == VK_SHIFT){
                    (msgToSave)->shiftActive = 1;
                }
            }
        }
    }
    return 0;
}

int isAlphabeticalKey(int key){
    return (key >= 0x30 && key <= 0x39) || (key >= 0x41 && key <= 0x5A) || key == VK_SPACE;
}
