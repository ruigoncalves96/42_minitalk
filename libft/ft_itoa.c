/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:37:53 by randrade          #+#    #+#             */
/*   Updated: 2024/04/24 15:48:45 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_intmin(char *ptr)
{
	ptr[1] = '2';
	ptr[2] = '1';
	ptr[3] = '4';
	ptr[4] = '7';
	ptr[5] = '4';
	ptr[6] = '8';
	ptr[7] = '3';
	ptr[8] = '6';
	ptr[9] = '4';
	ptr[10] = '8';
	return (ptr);
}

static char	*ft_convert(char *ptr, int n)
{
	if (n < 0)
	{
		*ptr = '-';
		if (n == -2147483648)
			return (ft_intmin(ptr));
		n *= -1;
		ptr++;
	}
	if (n < 10)
	{
		*ptr = n + 48;
	}
	else
	{
		ptr = ft_convert(ptr, n / 10);
		ptr = ft_convert(ptr + 1, n % 10);
	}
	return (ptr);
}

static int	ft_digitlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		digit_len;

	digit_len = ft_digitlen(n);
	if (n < 0)
		digit_len++;
	ptr = ft_calloc((digit_len + 1), sizeof(char));
	if (ptr != NULL)
	{
		ft_convert(ptr, n);
		ptr[digit_len] = '\0';
	}
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i = -5859;;
	char	*nbr = ft_itoa(i);

	printf("%s\n", nbr);
	printf("%d\n", nbr[5]);

	free(nbr);
}
*/
/*

----- Parameters -----

	n: the integer to convert.

----- Return value -----

	The string representing the integer.
	NULL if the allocation fails.

----- External functs -----

	malloc.

----- Description -----

	Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
	Negative numbers must be handled.
   */
