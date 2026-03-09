#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("\n Ошибка: дочерний процесс не был создан! \n");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        printf("child pid = %d\n", getpid());
        exit(5);
    }
    else
    {
        printf("parent pid = %d\n", getpid());
        wait(&status);
        printf("child process status = %d\n", WEXITSTATUS(status));
    }

    return 0;
}
