/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:33:48 by randrade          #+#    #+#             */
/*   Updated: 2024/04/26 14:48:10 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chrcmp(char const *s1, char const *set)
{
	while (*set)
	{
		if (*s1 == *set)
			return (1);
		else
			set++;
	}
	return (0);
}

static int	ft_first_trim(char const *s1, char const *set)
{
	int	trim_nbr;

	trim_nbr = 0;
	while (ft_chrcmp(s1, set))
	{
		trim_nbr++;
		s1++;
	}
	return (trim_nbr);
}

static int	ft_last_trim(char const *s1, char const *set, unsigned int s_len)
{
	int	trim_nbr;

	s1 += s_len - 1;
	trim_nbr = 0;
	while (ft_chrcmp(s1, set))
	{
		trim_nbr++;
		s1--;
	}
	return (trim_nbr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		s1_len;
	int		f_trim;
	int		l_trim;

	if (!*s1)
		return (ft_strdup(""));
	s1_len = ft_strlen(s1);
	f_trim = ft_first_trim(s1, set);
	l_trim = ft_last_trim(s1, set, s1_len);
	s1_len = s1_len - f_trim - l_trim;
	if (s1_len <= 0)
		return (ft_strdup(""));
	ptr = malloc(s1_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s1[f_trim], s1_len + 1);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str = "Free the duck!";
	char	*set = "";
	char	*result = ft_strtrim(str, set);
	
	printf("%s\n", result);

	free (result);
}*/
