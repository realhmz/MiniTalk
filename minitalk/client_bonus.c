#include <signal.h>
#include <stddef.h>
#include <unistd.h>

int ft_atoi(char *str)
{
    int i;
    int sign;
    int res;

    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res * sign);
}

char *str;

void    bit_sender(int signum,siginfo_t *info,void *ptr)
{
    static int i = 0;
    static int j = 0;
    int bit;
    if (signum == SIGUSR1)
        bit = 1;
    else
        bit = 0;
    if (bit == ((str[i] >> j) & 1))
    {
        j++;
        if (j == 8)
        {
            i++;
            j = 0;
            if (str[i] == '\0')
            {
                write(1, "Message sent\n", 13);
                kill(info->si_pid, SIGUSR2);
            }
        }
        kill(info->si_pid, SIGUSR1);
    }
    if (signum == 0)
    {
        return ;
    }
    else
    {
        write(1, "Error\n", 6);
        kill(info->si_pid, SIGUSR2);
    }   
}

void    handler(int signum,siginfo_t *info, void *ptr)
{
    if (signum == SIGUSR1)
        bit_sender(signum,info,ptr);
    else if (signum == SIGUSR2)
        return ;
}
void    send_first_bit(int pid)
{
    int bit;
            bit = (str[0] >> 0) & 1;
            if (bit == 1)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
}
int pid;
int main(int ac, char **av)
{
    struct  sigaction   action;
    if(ac != 3)
        return 1;
    pid = ft_atoi(av[1]);
    str = av[2];
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    send_first_bit(pid);
    while (1)
        pause();
    return 0;
}  
 