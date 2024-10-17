#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>

int main () {
    struct utsname uname_info;
    if (uname(&uname_info) < 0)
        exit(EXIT_FAILURE);

    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("process ID: %d\n", pid);
    printf("parent process ID: %d\n", ppid);
    printf("system: %s\n", uname_info.sysname);
    printf("node: %s\n", uname_info.nodename);
    printf("release: %s\n", uname_info.release);
    printf("version: %s\n", uname_info.version);
    printf("machine: %s\n", uname_info.machine);

    return 0;
}
