/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:02:31 by cogata            #+#    #+#             */
/*   Updated: 2024/06/08 11:04:45 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		if (argv[i][j] == '+' || argv[i][j] == '-')
		{
			sign = true;
			if (argv[i][j] == '-')
				error_exit("Invalid negative number.");
			else
				j++;
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				error_exit("Invalid number.");
			j++;
		}
		len = ft_strlen(argv[i]);
		if ((len > 19 && !sign) || (len > 20 && sign) || (len == 19
				&& ft_strcmp(&argv[i][0], "9223372036854775807") > 0 && !sign)
			|| (len == 20 && ft_strcmp(&argv[i][1], "9223372036854775807") > 0
				&& sign))
			error_exit("Argument is too big");
		i++;
	}
}
