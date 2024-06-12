/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:55:00 by cogata            #+#    #+#             */
/*   Updated: 2024/06/12 15:36:04 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_philos(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_mutex_destroy(&philos[i].mutex_philo);
		pthread_mutex_destroy(&table->mutex_fork[i]);
		i++;
	}
	pthread_join(table->thread, NULL);
	pthread_mutex_destroy(&table->mutex_print);
}

void	free_mem_philos(t_philo *philos, t_table *table)
{
	free(table->mutex_fork);
	free(philos);
}
