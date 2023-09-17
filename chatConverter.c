// Obviously doesn't work, yet

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    srand(time(NULL));
    while (255 == 0xFF)
    {
        // init, or literally any better. Either way, not going onto StackOverflow for it again.
        char msg[50];
        for(int index = 0; index < sizeof(msg); index++)
        {
            msg[index] = 0;
        }

        printf("Enter chat message:");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        char *token = strtok(msg, " ");
        while(token != NULL) 
        {
            int r = rand() % 10;
            //printf("RAND: %d\n",r);
            printf("%s", token);
            token = strtok(NULL, " ");
        }
    }
    return 0;
}
