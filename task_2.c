#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define DEFAULT_TIME 5

int main (int argc, char* argv[]) {
    time_t duration;
    
    if (argc > 1) { duration = atoi(argv[1]); } 
    else { duration = DEFAULT_TIME; }

    pid_t pid = fork();
    if (pid < 0) { exit(EXIT_FAILURE); }

    if (pid == 0) {
        time_t start_time = time(NULL);

        int count = 0;
        while (time(NULL) - start_time < duration)
            count++;

        printf("child process (PID: %d) executed %d iterations\n", getpid(), count);
        exit(EXIT_SUCCESS);
    } 
    else {
        time_t start_time = time(NULL);

        int count = 0;
        while (time(NULL) - start_time < duration)
            count++;

        printf("parent process (PID: %d) executed %d iterations\n", getpid(), count);
        wait(NULL);
    }

    return 0;
}
