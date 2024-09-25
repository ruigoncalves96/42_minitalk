/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniclient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:36:02 by randrade          #+#    #+#             */
/*   Updated: 2024/09/25 16:46:32 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_parsing_check(int argc, char *str)
{
	int	i;

	if (argc != 3)
	{
		ft_putstr_fd("\n -xxx- Wrong format! Please, try again. -xxx-\n\n", 1);
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
		{
			ft_putstr_fd("\n -xxx- Wrong PID Format! Please, try again. ", 1);
			ft_putstr_fd("-xxx-\n\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_sendbit(unsigned int c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 1)
		{
			if (kill(pid, SIGUSR1) != 0)
				return (1);
		}
		else
		{
			if (kill(pid, SIGUSR2) != 0)
				return (1);
		}
		usleep(10);
		i--;
	}
	return (0);
}

int	ft_sendmessage(char *str, int pid)
{
	int	i;

	while (*str)
	{
		if (ft_sendbit(*str, pid) != 0)
			return (1);
		str++;
	}
	i = 0;
	while (i < 8)
	{
		if (kill(pid, SIGUSR2) != 0)
			return (1);
		usleep(10);
		i++;
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

	if (ft_parsing_check(argc, argv[1]) == 1)
		return (1);
	signal(SIGUSR1, &ft_signal_handle);
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) != 0)
	{
		ft_putstr_fd("\n-xxx- Wrong PID connection! Please, try again. ", 1);
		ft_putstr_fd("-xxx-\n\n", 1);
		return (1);
	}
	if (ft_sendmessage(argv[2], pid) != 0)
	{
		printf("\n-xxx- Failed to send message! Please, try again. -xxx-\n\n");
		return (1);
	}
	return (0);
}
