/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:55:00 by cogata            #+#    #+#             */
/*   Updated: 2024/06/13 13:53:16 by cogata           ###   ########.fr       */
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
		i++;
	}
	pthread_join(table->thread, NULL);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos[i].mutex_philo);
		pthread_mutex_destroy(&table->mutex_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->mutex_dead);
	pthread_mutex_destroy(&table->mutex_full);
	pthread_mutex_destroy(&table->mutex_print);
}

void	free_mem_philos(t_philo *philos, t_table *table)
{
	free(table->mutex_fork);
	free(philos);
}
