/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/10 17:04:21 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philos;

	//VALIDATE ARGUMENTS
	validate_arguments(argc, argv);
	//GET ARGUMENTS AND INIT DATA
	init_data(&table, &philos, argc, argv);
	//CREATE PHILOS AND MONITOR
	create_philos(&table, philos);
	//WAIT PHILOS TO EXIT
	wait_philos(&table, philos);
}
