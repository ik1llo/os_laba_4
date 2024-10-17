#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0)
        return EXIT_FAILURE;

    if (pid == 0) {
        printf("child process (PID: %d) is created and will become a zombie\n", getpid());
        
        sleep(10); 
        exit(0);
    } else {
        printf("parent process (PID: %d) is waiting before calling ps\n", getpid());
        sleep(2); 
        
        printf("\nrunning processes before wait():\n");
        system("ps -f");
        wait(NULL); 

        printf("\nrunning processes after wait():\n");
        system("ps -f");

        printf("\nchild process has been terminated\n");
    }

    return EXIT_SUCCESS;
}
