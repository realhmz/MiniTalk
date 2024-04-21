#include <unistd.h>
#include <signal.h>
#include <stddef.h>

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

void singal_handler(int pid, char *str)
{
    int i;
    int j;
    int bit;

    i = 0;
    while (str[i])
    {
        j = 0;
        while (j < 8)
        {
            bit = (str[i] >> j) & 1;
            if (bit == 1)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            j++;
            usleep(100);
        }
        i++;
    }
}


int main(int ac,char **av)
{
    if (ac == 3)
    {
        int pid;

        pid = ft_atoi(av[1]);
        singal_handler(pid,av[2]);
    }
    else
    {
        write(1, "ERROR !!\n", 9);
    }
}


// Tasks ;
// 1. Create a client that sends a message to the server
// 2. Create a server that receives the message from the client