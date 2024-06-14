/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:30:47 by cogata            #+#    #+#             */
/*   Updated: 2024/06/14 16:56:10 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	error_exit(char *error)
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
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

size_t	ft_long_atoi(const char *nptr)
{
	char	*nbr;
	int		i;
	size_t	sign;
	size_t	res;

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

char	*ft_copy_str(char const *s1, char const *s2, char *res)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	ft_copy_str(s1, s2, res);
	return (res);
}

long long	ft_count_divider(long nb)
{
	long long	divider;

	if (nb == 0)
		return (1);
	divider = 1;
	while (nb > 0)
	{
		nb = nb / 10;
		divider = divider * 10;
	}
	divider = divider / 10;
	return (divider);
}

char	*ft_init_str(long nb, char *res, int count, int is_negative)
{
	int		i;
	long	divider;

	divider = ft_count_divider(nb);
	i = 0;
	if (is_negative == 1)
	{
		res[0] = '-';
		i++;
	}
	while (i < count)
	{
		res[i] = (nb / divider) + '0';
		nb = nb % divider;
		divider = divider / 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_count_num(long nb)
{
	int	count;

	count = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		count;
	char	*res;
	int		is_negative;

	nb = n;
	is_negative = 0;
	if (nb < 0)
	{
		nb = nb * (-1);
		count = ft_count_num(nb) + 1;
		is_negative = 1;
	}
	else if (nb == 0)
		count = 1;
	else
		count = ft_count_num(nb);
	res = malloc((count + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_init_str(nb, res, count, is_negative);
	return (res);
}