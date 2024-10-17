#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    int throws = atoi(argv[1]);
    int pipefd[2];

    if (pipe(pipefd) == -1)
        return 1;

    pid_t pid = fork();
    if (pid < 0) 
        return 1;

    if (pid == 0) {
        close(pipefd[0]);
        int points_inside_circle = 0;

        srand(time(NULL));
        for (int k = 0; k < throws; k++) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;

            if ((x * x + y * y) <= 1.0)
                points_inside_circle++;
        }

        write(pipefd[1], &points_inside_circle, sizeof(points_inside_circle));
        close(pipefd[1]);

        exit(0);
    } 
    else {
        close(pipefd[1]);
        int points_inside_circle = 0;

        read(pipefd[0], &points_inside_circle, sizeof(points_inside_circle));
        close(pipefd[0]);

        wait(NULL);

        double pi = (4.0 * points_inside_circle) / throws;
        printf("points inside the circle: %d\n", points_inside_circle);
        printf("calculated π: %f\n", pi);
    }

    return 0;
}
