#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>


void    ft_putnbr(int n)
{
    char c;
    if (n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void    message_handler(int signum, siginfo_t *info, void *ptr)
{
    static int pid = 0;
    static int i = 0;
    static char c = 0;
    if (pid == 0)
        pid = info->si_pid;
    if(pid != info->si_pid)
        exit(1);
    c = (c << 1) | (signum == SIGUSR1);
    i++;
    if (i % 8 == 0)
    { 
        if (!c)
        {
            write(1, "\n", 1);
            kill(info->si_pid,SIGUSR2);
            pid = 0;
        }
        else
        {
            write(1, &c, 1);
        }
        i = 0;
        c = '\0';
    }
    usleep(100);
    kill(info->si_pid,SIGUSR1);
}
int main(int ac, char **av)
{
    struct  sigaction   action;
    int pid = getpid();
    ft_putnbr(pid);
    write(1, "\n", 1);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = message_handler;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
    {
        pause();
    }
    return 0;
}   