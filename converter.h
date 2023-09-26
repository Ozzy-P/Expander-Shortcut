#include <windows.h>

#ifndef MESSAGE
#define MESSAGE
extern const int MAX_CHARS;
struct message {
    HGLOBAL hMem;
    char *msg;
    int currentCharCount;
};
void formatToHexStatic(struct message *msgToCopy, char *hexValues);
void formatToHex(struct message *msgToCopy, char *hexValues);
void copyMessage(struct message *msgToCopy);
void clearArray(struct message *msgToClear);
void saveToFile(int msgSize, char *msg[msgSize], char *file);
struct message *createMessage();
#endif
