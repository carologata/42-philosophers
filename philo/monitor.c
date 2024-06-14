/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:00 by cogata            #+#    #+#             */
/*   Updated: 2024/06/13 15:33:23 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_last_meal_time(t_philo *philos, int i)
{
	if (get_current_time(philos[i].table) > get_units(&philos[i].mutex_philo,
			&philos[i].last_meal_time) + philos[i].table->time_to_die)
	{
		safe_printf(&philos[i], DIED);
		set_status(&philos[i].table->mutex_dead, &philos[i].table->is_dead,
			true);
		return (true);
	}
	return (false);
}

void	*monitor_philos(void *arg)
{
	int		i;
	t_table	*table;
	t_philo	*philos;
	int		philos_are_full;

	philos = (t_philo *)arg;
	table = philos[0].table;
	while (1)
	{
		i = 0;
		philos_are_full = 0;
		while (i < table->number_of_philosophers)
		{
			if (get_units(&philos[i].mutex_philo,
					&philos[i].meals_eaten) >= table->number_of_meals)
				philos_are_full++;
			if (philos_are_full == table->number_of_philosophers)
			{
				set_status(&philos[i].table->mutex_full,
					&philos[i].table->are_full, true);
				return (NULL);
			}
			if (check_last_meal_time(philos, i))
				return (NULL);
			i++;
		}
	}
}