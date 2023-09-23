// Obviously doesn't work, yet, or maybe ever.

/*
    TODO: [W] *Fix capitalization, somehow. Preferrably just capitalize the first letter then [REDACTED].
          [D] *Add copy and paste functionality from chatConverter.c
          [D] *Attempt to auto paste (probably not needed, esp if its a mist).
*/

#include <windows.h>
#include <stdio.h>

int Save(int _key, char *file);
int SaveInt(int number, char *file);
const int MAX_CHARS = 50;
const char *hex = "#ffe000#ff0000#ffbb1e#5fff1e#8df9ea#8dacf9#5b16b9#b481fa#fa81eb#cd4040";

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
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, 7*MAX_CHARS);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    fprintf(OUTPUT_FILE, "START\n");
    int activeKey = 1;
    int pressedChars[255+8];

    char typedChars[MAX_CHARS];
    char allocConvert[MAX_CHARS * 7 + 1];
    int numberChars = 0;

    for(int iteration = 0; iteration < 255+8; iteration++){
        pressedChars[iteration] = 0;
    }

    for(int iteration = 0; iteration < sizeof(typedChars); iteration++){
        typedChars[iteration] = 0;
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

                char *token = strtok(typedChars, " ");
                while(token != NULL) {
                    int r = rand() % 10;
                    strcat(allocConvert,"(");
                    strncat(allocConvert,hex+(r*7),7);
                    strcat(allocConvert,"/");   
                    strcat(allocConvert,token);   
                    strcat(allocConvert,") ");  
                    token = strtok(NULL, " ");
                }

                memcpy(GlobalLock(hMem), allocConvert, sizeof(allocConvert));
                GlobalUnlock(hMem);
                OpenClipboard(0);
                EmptyClipboard();
                SetClipboardData(CF_TEXT, hMem);
                CloseClipboard();
                GlobalFree(hMem);
                break;
            }
            if (!(keyState) && (pressedChars[i] == 1)){
                fprintf(OUTPUT_FILE, "%s", &i);
                //fprintf(OUTPUT_FILE, "RELEASED:%s,%d\n", &i,i);
                typedChars[numberChars] = i;
                numberChars++;
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
