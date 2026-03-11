#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t process1_pid, process2_pid;
    int status1, status2;

    process1_pid = fork();

    switch (process1_pid)
    {
        case -1:
            perror("\n Ошибка: process1 не был создан! \n");
            exit(EXIT_FAILURE);
            break;
            
        case 0:
            printf("process1: pid = %d, ppid = %d\n", getpid(), getppid());
            
            int status3;
            pid_t process3_pid = fork();

            switch (process3_pid)
            {
                case -1:
                    perror("\n Ошибка: process3 не был создан! \n");
                    exit(EXIT_FAILURE);
                    break;
                    
                case 0:
                    printf("process3: pid = %d, ppid = %d\n", getpid(), getppid());
                    exit(3);
                    break;
                    
                default:
                    break;
            }

            int status4;
            pid_t process4_pid = fork();

            switch (process4_pid)
            {
                case -1:
                    perror("\n Ошибка: process4 не был создан! \n");
                    exit(EXIT_FAILURE);
                    break;
                    
                case 0:
                    printf("process4: pid = %d, ppid = %d\n", getpid(), getppid());
                    exit(4);
                    break;
                    
                default:
                    break;
            }

            wait(&status3);
            wait(&status4);
            printf("status3 = %d\n", WEXITSTATUS(status3));
            printf("status4 = %d\n", WEXITSTATUS(status4));

            exit(1);
            break;
            
        default:
            break;
    }

    process2_pid = fork();

    switch (process2_pid)
    {
        case -1:
            perror("\n Ошибка: process2 не был создан! \n");
            exit(EXIT_FAILURE);
            break;
            
        case 0:
            printf("process2: pid = %d, ppid = %d\n", getpid(), getppid());
            
            int status5;
            pid_t process5_pid = fork();

            switch (process5_pid)
            {
                case -1:
                    perror("\n Ошибка: process5 не был создан! \n");
                    exit(EXIT_FAILURE);
                    break;
                    
                case 0:
                    printf("process5: pid = %d, ppid = %d\n", getpid(), getppid());
                    exit(5);
                    break;
                    
                default:
                    break;
            }

            wait(&status5);
            printf("status5 = %d\n", WEXITSTATUS(status5));
            exit(2);
            break;
            
        default:
            printf("parent pid = %d\n", getpid());
            wait(&status1);
            wait(&status2);
            printf("status1 = %d\n", WEXITSTATUS(status1));
            printf("status2 = %d\n", WEXITSTATUS(status2));
            break;
    }

    return 0;
}