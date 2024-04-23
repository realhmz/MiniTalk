/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:40:49 by het-taja          #+#    #+#             */
/*   Updated: 2024/04/23 18:34:03 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

void	handel_pid(int *i, int *pid, int info_pid)
{
	if (*pid == 0)
		*pid = info_pid;
	if (*pid != info_pid)
	{
		if (kill(*pid, 0) == -1)
		{
			*pid = 0;
			i = 0;
		}
		else
			kill(info_pid, SIGUSR2);
	}
}

void	message_handler(int signum, siginfo_t *info, void *ptr)
{
	static int	pid = 0;
	static int	i = 0;
	static char	c = 0;

	ptr = NULL;
	handel_pid(&i, &pid, info->si_pid);
	if (i == 0)
		c = 0;
	c = (c << 1) | (signum == SIGUSR1);
	i++;
	if (i % 8 == 0)
	{
		if (!c)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
			pid = 0;
		}
		else
			write(1, &c, 1);
		i = 0;
		c = '\0';
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct sigaction	action;
	int					pid;

	if (av)
		av = NULL;
	if (ac != 1)
	{
		return (1);
	}
	pid = getpid();
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
	return (0);
}
