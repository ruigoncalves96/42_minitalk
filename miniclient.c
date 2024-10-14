/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniclient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:36:02 by randrade          #+#    #+#             */
/*   Updated: 2024/10/12 18:43:26 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_miniclient	g_talk;

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

void	ft_sendbit(void)
{
	usleep(SLEEP_TIME);
	if (((*g_talk.message >> g_talk.shift) & 1) == 1)
		kill(g_talk.pid, SIGUSR1);
	else
		kill(g_talk.pid, SIGUSR2);
	g_talk.bits++;
	g_talk.shift--;
	if (g_talk.bits == 8)
	{
		g_talk.bits = 0;
		g_talk.shift = 7;
		g_talk.message++;
	}
}

void	ft_handle_signal(int signum)
{
	if (signum == SIGUSR1)
		ft_sendbit();
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("Message delivered\n", 1);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	if (ft_parsing_check(argc, argv[1]) == 1)
		return (1);
	g_talk.message = argv[2];
	g_talk.bits = 0;
	g_talk.shift = 7;
	g_talk.pid = ft_atoi(argv[1]);
	if (g_talk.pid <= 0 || kill(g_talk.pid, 0) != 0)
	{
		ft_putstr_fd("\n-xxx- Wrong PID connection! Please, try again. ", 1);
		ft_putstr_fd("-xxx-\n\n", 1);
		return (1);
	}
	signal(SIGUSR1, ft_handle_signal);
	signal(SIGUSR2, ft_handle_signal);
	ft_sendbit();
	while (1)
	{
		pause();
	}
	return (0);
}
