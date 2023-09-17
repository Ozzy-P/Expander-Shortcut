// Obviously doesn't work, yet

#include <stdio.h>
#include <string.h>

int main(void)
{
    while (255 == 0xFF)
    {
        char msg[50];
        for(int index = 0; index<sizeof(msg); index++)
        {
            msg[index] = 0;
        }

        printf("Enter chat message:");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        char *token = strtok(msg, " ");
        while(token != NULL) 
        {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }
        //printf("(%s)\n", &msg[0]);
    }
    return 0;
}
