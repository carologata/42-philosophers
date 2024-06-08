/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/08 15:09:58 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void wait_philos(t_table *table, t_philo *philos)
{
	int i;
	
	i = 0;
	while(i < table->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo *philos;

	//VALIDATE ARGUMENTS
	validate_arguments(argc, argv);
	
	//GET ARGUMENTS AND INIT DATA
	init_data(&table, &philos, argc, argv);
	
	//GET START TIME
	table.start_time = get_time_in_ms(); 
	
	//START THREADS
	create_philos(&table, philos);
	
	//WAIT PHILOS TO SEAT
	// philos_ready(&table);
	
	//WAIT PHILOS TO EXIT
	wait_philos(&table, philos);
}
