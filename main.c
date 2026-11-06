#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main(void) {
    char line[1024];

    while(true) {
        printf("husk> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "exit") == 0) {
            break;
        }
        char *args[64];
        int count = 0;
        char *word = strtok(line," ");
        while (word != NULL) {
            if (count > 62) {
                break;
            }
            args[count] = word;
            count++;
            word = strtok(NULL, " ");
        }
        for (int i = 0; i < count; i++) {
            printf("[%s]\n", args[i]);
        }
        args[count] = NULL;

    }

}
