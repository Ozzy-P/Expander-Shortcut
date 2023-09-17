// Obviously doesn't work, yet

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *hex = "#ffe000#ff0000#ffbb1e#5fff1e#8df9ea#8dacf9#5b16b9#b481fa#fa81eb#cd4040";
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

            printf("(");
            for(int hexV = r*7; hexV < (r*7)+7; hexV++)
            printf("%c", hex[hexV]);

            printf("/");    
            printf("%s", token);
            printf(") "); 
            token = strtok(NULL, " ");
        }
        printf("\n");
    }
    return 0;
}
