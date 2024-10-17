/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:22:38 by randrade          #+#    #+#             */
/*   Updated: 2024/10/17 13:37:43 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_miniclient
{
	unsigned int	len;
	pid_t			pid;
	char			*message;
	int				bits;
	int				shift;
	int				siginfo;
	int				stage;
}	t_miniclient;

typedef struct s_miniserver
{
	unsigned int	bytes;
	pid_t			pid;
	char			*message;
	int				bits;
	int				siginfo;
	int				stage;
}	t_miniserver;

#endif
