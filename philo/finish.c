/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:55:00 by cogata            #+#    #+#             */
/*   Updated: 2024/06/11 17:28:38 by cogata           ###   ########.fr       */
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
}

void free_mem_philos(t_philo *philos, t_table *table)
{
	int i;

	i = 0;
	while(i < table->number_of_philosophers)
	{
		free(&philos[i]);
		free(&table->mutex_fork[i]);
		i++;
	}
}