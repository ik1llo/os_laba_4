#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int custom_system (const char* command) {
    pid_t pid = fork();

    if (pid < 0) 
        return -1;
    
    if (pid == 0) {
        char* argv[3];

        argv[0] = "sh";
        argv[1] = "-c";
        argv[2] = (char*) command;
        argv[3] = NULL;

        execvp(argv[0], argv);
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
        
        return WEXITSTATUS(status);
    }
}

int main() {
    const char* command = "ls";
    int result = custom_system(command);

    printf("command exited with status: %d\n", result);
    return 0;
}
