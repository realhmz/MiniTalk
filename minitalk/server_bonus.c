#include <signal.h>
#include <stddef.h>
#include <unistd.h>

int recived(int signum)
{
    if(signum)
        return (1);
    else
        return (0);
}
void    ft_putnbr(int n)
{
    char c;
    if (n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void    message_handler(int signum,siginfo_t *info, void *ptr)
{
    static int i = 0;
    static char c = 0;

    if (signum == SIGUSR1)
        c = c | (1 << i);
    i++;
    kill(info->si_pid,SIGUSR1);
    if (i == 8)
    { 
        if (!c)
        {
            kill(info->si_pid,SIGUSR2);
            write(1,"finish",6);
        }
        else
            write(1, &c, 1);
        i = 0;
        c = '\0';
    }
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