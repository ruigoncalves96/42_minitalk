/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniclient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:36:02 by randrade          #+#    #+#             */
/*   Updated: 2024/09/24 23:55:10 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_getbit(unsigned int num, int position)
{
	return ((num >> position) & 1);
}

int	ft_sendbit(char *str, int pid)
{
	int	i;

	while (*str)
	{
		i = 7;
		while (i >= 0)
		{
			if (ft_getbit(*str, i) == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i--;
			usleep(100);
		}
		str++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		i++;
		usleep(50);
	}
	return (0);
}

void	ft_signal_handle(int signum)
{
	(void)signum;
	ft_putstr_fd("\n*** Message delivered with success ***\n\n", 1);
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Wrong format\n", 1);
		return (1);
	}
	while (*argv[1])
	{
		if (ft_isdigit(*argv[1]) != 1)
			return (1);
		(argv[1])++;
	}
	signal(SIGUSR1, &ft_signal_handle);
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) != 0)
	{
		ft_putstr_fd("Invalid PID, try again\n", 1);
		return (1);
	}
	if (ft_sendbit(argv[2], pid) != 0)
	{
		printf("Failed to send message! Please try again.\n");
		return (1);
	}
	return (0);
}
