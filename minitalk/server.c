#include <unistd.h>
#include <signal.h>
#include <stddef.h>

void    ft_putnbr(int n)
{
    char c;
    if (n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void    message_handler(int signum)
{
    static int i = 0;
    static char c = 0;

    if (signum == SIGUSR1)
        c = c | (1 << i);
    i++;
    if (i == 8)
    { 
        if (!c)
            write(1, "\n", 1);
        else
            write(1, &c, 1);
        i = 0;
        c = '\0';
    }
}

int main()
{
    int pid;
    struct  sigaction   action;
    action.sa_flags = SIGINFO;
    action.sa_handler = message_handler;
    char *msg;
    pid = getpid();
    ft_putnbr(pid);
    write(1, "\n", 1);
    signal(SIGUSR1, message_handler);
    signal(SIGUSR2, message_handler);

    while(1)
    {
        pause();
    }
    return 0;
}