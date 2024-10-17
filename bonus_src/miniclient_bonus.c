/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniclient_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:36:02 by randrade          #+#    #+#             */
/*   Updated: 2024/10/17 14:06:19 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

// SIGUSR 1 = Permission to send signal
// SIGUSR 2 = Message sent with success
//
// g_talk.stage 0 = Send strlen;
// g_talk.stage 1 = Send message;
//

t_miniclient	g_talk;

int	ft_parsing(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
	{
		ft_putstr_fd("\n -xxx- Wrong format! -xxx-\n\n", 1);
		return (1);
	}
	i = 0;
	while (argv[1][i])
	{
		if (ft_isdigit(argv[1][i]) != 1)
		{
			ft_putstr_fd("\n -xxx- Wrong PID Format! -xxx-\n\n", 1);
			return (1);
		}
		i++;
	}
	if (argv[1][0] == '\0' || argv[2][0] == '\0')
	{
		ft_putstr_fd("\n-xxx- Error!No PID or Message inserted! -xxx-\n\n", 1);
		return (1);
	}
	return (0);
}

void	ft_send_message(void)
{
	if (((*g_talk.message >> g_talk.shift) & 1) == 1)
		g_talk.siginfo = 1;
	else
		g_talk.siginfo = 2;
	g_talk.bits++;
	g_talk.shift--;
	if (g_talk.bits == 8)
	{
		g_talk.bits = 0;
		g_talk.shift = 7;
		g_talk.message++;
	}
}

void	ft_send_len(void)
{
	if (((g_talk.len >> g_talk.shift) & 1) == 1)
		g_talk.siginfo = 1;
	else
		g_talk.siginfo = 2;
	g_talk.bits++;
	g_talk.shift--;
	if (g_talk.bits == 32)
	{
		g_talk.bits = 0;
		g_talk.shift = 7;
		g_talk.stage = 1;
	}
}

void	ft_handle_signal(int signum)
{
	if (signum == SIGUSR1)
	{
		if (g_talk.stage == 0)
			ft_send_len();
		else if (g_talk.stage == 1)
			ft_send_message();
	}
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("\n##### - Message delivered - #####\n\n", 1);
		exit(0);
	}
	if (g_talk.siginfo == 1)
		kill(g_talk.pid, SIGUSR1);
	else if (g_talk.siginfo == 2)
		kill(g_talk.pid, SIGUSR2);
}

int	main(int argc, char *argv[])
{
	if (ft_parsing(argc, argv) == 1)
		return (1);
	g_talk.pid = ft_atoi(argv[1]);
	if (g_talk.pid <= 0 || kill(g_talk.pid, 0) != 0)
	{
		ft_putstr_fd("\n-xxx- Error on PID connection! -xxx-\n\n", 1);
		return (1);
	}
	g_talk.message = argv[2];
	g_talk.len = ft_strlen(g_talk.message);
	g_talk.bits = 0;
	g_talk.shift = 31;
	g_talk.stage = 0;
	signal(SIGUSR1, ft_handle_signal);
	signal(SIGUSR2, ft_handle_signal);
	ft_send_len();
	if (g_talk.siginfo == 1)
		kill(g_talk.pid, SIGUSR1);
	else if (g_talk.siginfo == 2)
		kill(g_talk.pid, SIGUSR2);
	while (1)
	{
		pause();
	}
	return (0);
}
