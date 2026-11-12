#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(void) {
    char line[1024];
    char cwd[1024];

    while(true) {
        getcwd(cwd, sizeof(cwd));
        printf("husk:%s> ", cwd);
        fflush(stdout);
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
        args[count] = NULL;

        if (count == 0) {
            continue;
        }

        char *outfile = NULL;
        char *infile = NULL;


        for (int i = 0; i < count; i++) {
            if (strcmp(args[i], ">") == 0) {
                outfile = args[i+1];
                args[i] = NULL;
            } else if (strcmp(args[i], "<") == 0) {
                infile = args[i+1];
                args[i] = NULL;
            }
        }

        if (args[0] == NULL) {
            fprintf(stderr, "husk: missing command\n");
            continue;
        }

        if (strcmp(args[0], "cd") == 0) {
            char *dir;
            if (args[1] == NULL) {
                dir = getenv("HOME");
            } else {
                dir = args[1];
            }

            if (chdir(dir) != 0) {
                perror("husk");
            }
            continue;
        }



        pid_t pid = fork();


        if (pid == 0) {
            if (outfile != NULL) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 1);
                close(fd);
            }
            if (infile != NULL) {
                int fd = open(infile, O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 0);
                close(fd);
            }
            execvp(args[0], args);
            perror("husk");
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }

    }

}
