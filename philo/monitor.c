/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:00 by cogata            #+#    #+#             */
/*   Updated: 2024/06/19 17:49:49 by cogata           ###   ########.fr       */
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

bool	check_all_philos_full(t_philo *philo, t_table *table,
		int philos_are_full)
{
	if (philos_are_full == table->number_of_philosophers)
	{
		set_status(&philo->table->mutex_full, &philo->table->are_full, true);
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
			if (table->number_of_meals)
			{
				if (get_units(&philos[i].mutex_philo,
						&philos[i].meals_eaten) >= table->number_of_meals)
					philos_are_full++;
				if (check_all_philos_full(&philos[i], table, philos_are_full))
					return (NULL);
			}
			if (check_last_meal_time(philos, i))
				return (NULL);
			i++;
		}
	}
}
