/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:21:30 by randrade          #+#    #+#             */
/*   Updated: 2024/10/12 18:23:59 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_miniserver	g_talk;

void	ft_process_bits(void)
{
	if (g_talk.siginfo == 1)
		g_talk.bytes = (g_talk.bytes << 1) | 1;
	else if (g_talk.siginfo == 2)
		g_talk.bytes = g_talk.bytes << 1;
	g_talk.bits++;
	if (g_talk.bits == 8)
	{
		if (g_talk.bytes == 0)
			g_talk.siginfo = 0;
		else
			ft_putchar_fd(g_talk.bytes, 1);
		g_talk.bytes = 0;
		g_talk.bits = 0;
	}
}

void	ft_handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	g_talk.pid = info->si_pid;
	if (sig == SIGUSR1)
		g_talk.siginfo = 1;
	else if (sig == SIGUSR2)
		g_talk.siginfo = 2;
	ft_process_bits();
}

void	ft_sig_config(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_sigaction = &ft_handle_signal;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
}

int	main(void)
{
	ft_putstr_fd("##########\tPID: [", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("]\t##########\n\n", 1);
	g_talk.pid = 0;
	g_talk.siginfo = 0;
	g_talk.bytes = 0;
	g_talk.bits = 0;
	ft_sig_config();
	while (1)
	{
		pause();
		if (g_talk.siginfo == 0)
		{
			ft_putstr_fd("\n\n", 1);
			kill(g_talk.pid, SIGUSR2);
		}
		else
			kill(g_talk.pid, SIGUSR1);
	}
	return (0);
}
