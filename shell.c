#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_INPUT_SIZE 1024

int main() 
{
    char input[MAX_INPUT_SIZE];
    char *args[2];
    pid_t pid;

    while (1) 
    {
        printf("$ ");
        fflush(stdout); 
        
        if (fgets(input, sizeof(input), stdin) == NULL) 
        {
            /* Gérer la fin du fichier (Ctrl+D) */
            printf("\n");
            break;
        }
        input[strcspn(input, "\n")] = '\0';

        args[0] = input;
        args[1] = NULL;
      
	pid = fork();
        if (pid < 0) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        {
        if (execvp(args[0], args) == -1) 
            {
            perror("execvp");
                exit(EXIT_FAILURE);
            }
        } 
        else 
        {
            wait(NULL);
        }
    }

    return 0;
}
