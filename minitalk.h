/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:22:38 by randrade          #+#    #+#             */
/*   Updated: 2024/10/16 14:59:36 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

# ifndef SLEEP_TIME
#  define SLEEP_TIME 0
# endif

typedef struct s_miniclient
{
	pid_t	pid;
	char	*message;
	unsigned int		len;
	int		bits;
	int		shift;
	int		siginfo;
	int		stage;
}	t_miniclient;

typedef struct s_miniserver
{
	pid_t	pid;
	char	*message;
	unsigned int		bytes;
	int		bits;
	int		siginfo;
	int		stage;
}	t_miniserver;

#endif
