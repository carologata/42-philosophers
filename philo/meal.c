/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:05 by cogata            #+#    #+#             */
/*   Updated: 2024/06/10 18:33:36 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_meal(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->philo_died)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_right]);
		if (!philo->table->philo_died)
			safe_printf(philo, FORK);
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_left]);
		if (!philo->table->philo_died)
			safe_printf(philo, FORK);
		if (!philo->table->philo_died)
			safe_printf(philo, EAT);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_lock(&philo->table->mutex_philo);
		philo->last_meal_time = get_current_time(philo->table);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->table->mutex_philo);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_right]);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_left]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_left]);
		if (!philo->table->philo_died)
			safe_printf(philo, FORK);
		pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_right]);
		if (!philo->table->philo_died)
			safe_printf(philo, FORK);
		if (!philo->table->philo_died)
			safe_printf(philo, EAT);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_lock(&philo->table->mutex_philo);
		philo->last_meal_time = get_current_time(philo->table);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->table->mutex_philo);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_left]);
		pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_right]);
	}
}

void	sleep_philo(t_philo *philo)
{
	if (!philo->table->philo_died)
		safe_printf(philo, SLEEP);
	usleep(philo->table->time_to_sleep * 1000);

}

void	think(t_philo *philo)
{
	size_t time_to_think;

	time_to_think = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal_time) - philo->table->time_to_eat) / 2;
	if (!philo->table->philo_died)
		safe_printf(philo, THINK);
	usleep(time_to_think);
}
