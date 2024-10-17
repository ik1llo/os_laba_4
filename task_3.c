#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void child_process(int id) {
    printf("child process %d (PID: %d) is running\n", id, getpid());
    while (1)
        sleep(10);
}

int main (int argc, char* argv[]) {
    if (argc != 2)
        return EXIT_FAILURE;

    int children_count = atoi(argv[1]);
    if (children_count <= 0) 
        return EXIT_FAILURE;

    pid_t pids[children_count];

    for (int k = 0; k < children_count; k++) {
        pid_t pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);

        if (pid == 0) { child_process(k + 1); } 
        else { pids[k] = pid; }
    }

    sleep(3);

    printf("\nrunning processes:\n");
    for (int k = 0; k < children_count; k++) {
        printf("process %d (PID: %d):\n", k + 1, pids[k]);

        char command[50];
        snprintf(command, sizeof(command), "ps -p %d", pids[k]);
        system(command);
    }

    for (int k = 0; k < children_count; k++) {
        kill(pids[k], SIGTERM);
        waitpid(pids[k], NULL, 0);
    }

    printf("\nall child processes have been terminated\n");
    return EXIT_SUCCESS;
}
