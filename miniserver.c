/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:21:30 by randrade          #+#    #+#             */
/*   Updated: 2024/09/25 10:43:36 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_print_message(char c, siginfo_t *info)
{
	static char	*bin_buffer;
	char	bin[2];

	bin[0] = c;
	bin [1] = '\0';
	if (c == 0)
	{
		ft_putstr_fd(bin_buffer, 1);
		ft_putstr_fd("\n\n", 1);
		kill(info->si_pid, SIGUSR1);
		free (bin_buffer);
	}
	else
		bin_buffer = ft_strsjoin(bin_buffer, bin);
}

void	ft_handle_signal(int signum, siginfo_t *info, void *ucontext)
{
	static int	bits;
	static int	i;

	(void)ucontext;
	if (signum == SIGUSR1)
	{
		bits <<= 1;
		bits |= 1;
	}
	else if (signum == SIGUSR2)
		bits <<= 1;
	i++;
	if (i == 8)
	{
		ft_print_message((char)bits, info);
		i = 0;
		bits = 0;
	}
}

void	ft_sig_config(void)
{
	struct sigaction	action;

	action.sa_sigaction = &ft_handle_signal;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		return (ft_putstr_fd("Failed to set SIGUSR1\n", 1));
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		return (ft_putstr_fd("Failed to set SIGUSR2\n", 1));
}

int	main(void)
{
	ft_putstr_fd("##########\tPID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\t##########\n\n", 1);
	ft_sig_config();
	while (1)
	{
	}
	return (0);
}
