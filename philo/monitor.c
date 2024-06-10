/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:00 by cogata            #+#    #+#             */
/*   Updated: 2024/06/10 18:42:02 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_philos(void *arg)
{
	int		i;
	t_table	*table;
	t_philo	*philos;
	int all_philo_full;

	philos = (t_philo *)arg;
	table = philos[0].table;
	while (!table->philo_died)
	{
		i = 0;
		all_philo_full = 0;
		while (i < table->number_of_philosophers)
		{
			pthread_mutex_lock(&table->mutex_philo);
			if(philos[i].meals_eaten >= table->number_of_meals)
				all_philo_full++;
			if(all_philo_full == table->number_of_philosophers)
				table->all_full = true;
			if (philos[i].last_meal_time + philos[i].table->time_to_die < get_current_time(philos[i].table))
			{
				if (!philos[i].table->philo_died)
				{
					safe_printf(&philos[i], DIED);
					philos[i].table->philo_died = true;
					pthread_mutex_unlock(&philos->table->mutex_philo);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&philos->table->mutex_philo);
			i++;
		}
	}
	return (NULL);
}
