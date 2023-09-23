/* 
    Manual chat converter, single file to compile. Use the terminal to insert a message, then it will be returned. Not respecting more than limit.
    Part 1 Done
    Part 2 - Done - Auto copy to clipboard and hopefully don't set everything on fire in the process..
    Part 3 - Set a keybind.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winuser.h>

int copyToClipboard = 1;

int main(void){
    char *hex = "#ffe000#ff0000#ffbb1e#5fff1e#8df9ea#8dacf9#5b16b9#b481fa#fa81eb#cd4040";
    srand(time(NULL));

    while (255 == 0xFF){
        // init, or literally any better. Either way, not going onto StackOverflow for it again.
        char msg[50];
        char allocConvert[7*sizeof(msg)];
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, sizeof(allocConvert));

        for(int index = 0; index < sizeof(msg); index++){
            msg[index] = 0;
            allocConvert[index] = 0;
        }

        printf("Enter chat message:");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        char *token = strtok(msg, " ");
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
        printf("%s\n",allocConvert);
    }
    return 0;
}
