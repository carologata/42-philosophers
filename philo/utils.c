/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:30:47 by cogata            #+#    #+#             */
/*   Updated: 2024/06/05 15:00:32 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void error_exit(char *error)
{
	printf("%s\n", error);
	exit(1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

long	ft_long_atoi(const char *nptr)
{
	char		*nbr;
	int			i;
	int			sign;
	long int	res;

	nbr = (char *)nptr;
	i = 0;
	sign = 1;
	res = 0;
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13))
	{
		i++;
	}
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = res * 10 + nbr[i] - '0';
		i++;
	}
	return (res * sign);
}
