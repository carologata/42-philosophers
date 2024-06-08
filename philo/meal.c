/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:05 by cogata            #+#    #+#             */
/*   Updated: 2024/06/08 16:27:37 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_right]);
		safe_printf(philo, FORK);
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_left]);
		safe_printf(philo, FORK);
		safe_printf(philo, EAT);
		philo->timestamp_last_meal = get_current_time(philo->table);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_right]);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_left]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_left]);
		safe_printf(philo, FORK);
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_right]);
		safe_printf(philo, FORK);
		safe_printf(philo, EAT);
		philo->timestamp_last_meal = get_current_time(philo->table);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_left]);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_right]);
	}
}

void	sleep_philo(t_philo *philo)
{
	safe_printf(philo, SLEEP);
	usleep(philo->table->time_to_sleep * 1000);
	if(philo->timestamp_last_meal + philo->table->time_to_die >= get_current_time(philo->table))
	{
		philo->table->philo_died = true;
	}
	//check if someone is dead		
}

void	think(t_philo *philo)
{
	safe_printf(philo, THINK);
	if(philo->timestamp_last_meal + philo->table->time_to_die >= get_current_time(philo->table))
	{
		philo->table->philo_died = true;
	}
	//check if someone is dead		
}

void	*start_meal(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	// while (!philo->table->all_seat)
	// 	;

	while (1)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}

	return (NULL);
}