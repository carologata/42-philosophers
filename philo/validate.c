/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:02:31 by cogata            #+#    #+#             */
/*   Updated: 2024/06/13 15:32:54 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_sign(char *argv[], int i, int *j, bool *sign)
{
	if (argv[i][*j] == '+' || argv[i][*j] == '-')
	{
		*sign = true;
		if (argv[i][*j] == '-')
			error_exit("Invalid negative number.");
		else
			*j = *j + 1;
	}
}

void	check_zero(char *argv[])
{
	if (ft_long_atoi(argv[1]) == 0)
		error_exit("Number of philosophers must be bigger than 0");
}

void	validate_arguments(int argc, char *argv[])
{
	int		i;
	int		j;
	bool	sign;
	int		len;

	if (argc < 5 || argc > 6)
		error_exit("Invalid number of arguments.");
	i = 1;
	sign = false;
	while (argv[i])
	{
		j = 0;
		check_sign(argv, i, &j, &sign);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				error_exit("Invalid number.");
			j++;
		}
		len = ft_strlen(argv[i]);
		if (len > 20 || (len == 20 && ft_strcmp(&argv[i][0],
				"18446744073709551615") > 0))
			error_exit("Argument is too big");
		i++;
	}
	check_zero(argv);
}
