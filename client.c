/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:40:53 by het-taja          #+#    #+#             */
/*   Updated: 2024/04/23 18:32:02 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
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

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i + 1);
}

char	*g_str;

void	bit_sender(int pid)
{
	static size_t	i;
	static size_t	len;
	static int		bit = 0;

	if (!len)
		len = ft_strlen(g_str);
	if (i < len)
	{
		if ((g_str[i] >> (7 - bit)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		if (i == len - 1 && bit == 7)
			write(1, "Message sent !!\n", 16);
		if (bit % 8 == 0)
		{
			i++;
			bit = 0;
		}
	}
}

void	handler(int signum, siginfo_t *info, void *ptr)
{
	if (ptr)
		ptr = NULL;
	if (signum == SIGUSR1)
		bit_sender(info->si_pid);
	else if (signum == SIGUSR2)
		exit (1);
}

int	main(int ac, char **av)
{
	struct sigaction	action;
	int					pid;

	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	g_str = av[2];
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	bit_sender(pid);
	while (1)
		pause();
	return (0);
}
