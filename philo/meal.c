/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:05 by cogata            #+#    #+#             */
/*   Updated: 2024/06/12 15:32:29 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_meal(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_status(&philo->mutex_philo, &philo->table->is_dead)
		&& !get_status(&philo->mutex_philo, &philo->table->are_full))
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

void	get_forks_and_eat(t_philo *philo, int first_fork, int second_fork)
{
	size_t	end_meal_time;

	if (get_status(&philo->mutex_philo, &philo->table->is_dead)
		|| get_status(&philo->mutex_philo, &philo->table->are_full))
		return ;
	pthread_mutex_lock(&philo->table->mutex_fork[first_fork]);
	safe_printf(philo, FORK);
	pthread_mutex_lock(&philo->table->mutex_fork[second_fork]);
	safe_printf(philo, FORK);
	safe_printf(philo, EAT);
	set_units(&philo->mutex_philo, &philo->last_meal_time,
		get_current_time(philo->table));
	end_meal_time = get_current_time(philo->table) + philo->table->time_to_eat;
	while (get_current_time(philo->table) < end_meal_time
		&& !get_status(&philo->mutex_philo, &philo->table->is_dead)
		&& !get_status(&philo->mutex_philo, &philo->table->are_full))
		usleep(1000);
	set_units(&philo->mutex_philo, &philo->meals_eaten, philo->meals_eaten + 1);
	pthread_mutex_unlock(&philo->table->mutex_fork[first_fork]);
	pthread_mutex_unlock(&philo->table->mutex_fork[second_fork]);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		get_forks_and_eat(philo, philo->fork_right, philo->fork_left);
	else
		get_forks_and_eat(philo, philo->fork_left, philo->fork_right);
}

void	sleep_philo(t_philo *philo)
{
	size_t	end_sleep_time;

	if (get_status(&philo->mutex_philo, &philo->table->is_dead)
		|| get_status(&philo->mutex_philo, &philo->table->are_full))
		return ;
	safe_printf(philo, SLEEP);
	end_sleep_time = get_current_time(philo->table) + philo->table->time_to_eat;
	while (get_current_time(philo->table) < end_sleep_time
		&& !get_status(&philo->mutex_philo, &philo->table->is_dead)
		&& !get_status(&philo->mutex_philo, &philo->table->are_full))
		usleep(1000);
}

void	think(t_philo *philo)
{
	long	time_to_think;
	size_t	end_think_time;

	if (get_status(&philo->mutex_philo, &philo->table->is_dead)
		|| get_status(&philo->mutex_philo, &philo->table->are_full))
		return ;
	time_to_think = (long)(philo->table->time_to_die
			- (long)(get_current_time(philo->table)
				- (long)philo->last_meal_time)
			- (long)philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		return ;
	if (time_to_think > 500)
		time_to_think = 500;
	end_think_time = get_current_time(philo->table) + time_to_think;
	safe_printf(philo, THINK);
	while (get_current_time(philo->table) < end_think_time
		&& !get_status(&philo->mutex_philo, &philo->table->is_dead)
		&& !get_status(&philo->mutex_philo, &philo->table->are_full))
		usleep(1000);
}
