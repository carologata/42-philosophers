/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/13 13:52:03 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philos;

	philos = NULL;
	validate_arguments(argc, argv);
	init_data(&table, &philos, argc, argv);
	if (table.number_of_philosophers == 1)
	{
		pthread_create(&philos[0].thread, NULL, start_meal_alone, &philos[0]);
		pthread_join(philos[0].thread, NULL);
	}
	else
	{
		create_philos(&table, philos);
		wait_philos(&table, philos);
	}
	free_mem_philos(philos, &table);
}
