#include <windows.h>

#ifndef MESSAGE
#define MESSAGE
extern const int MAX_CHARS;
struct message {
    HGLOBAL hMem;
    char msg[50];
};
char *formatToHex(char *targetArray, char *messageArray, char *hexValues);
void copyMessage(HGLOBAL hMem, struct message *msgToCopy, int size);
void clearArray(struct message *msgToClear);
#endif
