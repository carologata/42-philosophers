/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:29:05 by cogata            #+#    #+#             */
/*   Updated: 2024/06/20 11:35:58 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_philo(t_philo *philo, t_table *table, int i)
{
	philo->id = i + 1;
	philo->last_meal_time = 0;
	philo->meals_eaten = 0;
	philo->table = table;
	philo->sem_print = init_sem(PRINT, 1);
	if (table->number_of_philosophers > 1)
	{
		philo->sem_philo = init_sem(CHILD, 1);
	}
}

void	start_child_process(t_table *table, int i)
{
	t_philo	philo;

	init_philo(&philo, table, i);
	create_thread_for_child(&philo);
	start_meal(&philo);
}

void	create_thread_for_child(t_philo *philo)
{
	pthread_t	monitor_is_dead;

	pthread_create(&monitor_is_dead, NULL, monitor_last_meal, philo);
}

void	*monitor_last_meal(void *arg)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		if (get_current_time(philo) > get_units(philo->sem_philo,
				&philo->last_meal_time) + philo->table->time_to_die)
		{
			print(philo, DIED);
			sem_post(philo->table->sem_is_dead);
			return (NULL);
		}
	}
	return (NULL);
}
