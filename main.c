#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main(void) {
    char line[1024];

    while(true) {
        printf("husk> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "exit") == 0) {
            break;
        }
        printf("you typed: [%s]\n", line);
    }

}
