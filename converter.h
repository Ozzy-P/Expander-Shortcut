#include <windows.h>

#ifndef MESSAGE
#define MESSAGE
extern const int MAX_CHARS;
struct message {
    HGLOBAL hMem;
    char msg[50];
};
void formatToHex(char *targetArray, struct message *msgToCopy, char *hexValues);
void copyMessage(HGLOBAL hMem, char *msgToCopy, int size);
void clearArray(struct message *msgToClear);
#endif
