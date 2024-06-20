/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:21:20 by cogata            #+#    #+#             */
/*   Updated: 2024/06/20 18:35:58 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	start_meal(t_philo *philo)
{
	while (1)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
}

void	eat(t_philo *philo)
{
	size_t	end_meal_time;

	sem_wait(philo->table->sem_door);
	sem_wait(philo->table->sem_forks);
	print(philo, FORK);
	sem_wait(philo->table->sem_forks);
	print(philo, FORK);
	set_units(philo->sem_philo, &philo->last_meal_time,
		get_current_time(philo));
	end_meal_time = get_current_time(philo) + philo->table->time_to_eat;
	print(philo, EAT);
	while (get_current_time(philo) < end_meal_time)
		usleep(1000);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_door);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->number_of_meals)
		sem_post(philo->table->sem_is_full);
}

void	sleep_philo(t_philo *philo)
{
	size_t	end_sleep_time;

	print(philo, SLEEP);
	end_sleep_time = get_current_time(philo) + philo->table->time_to_sleep;
	while (get_current_time(philo) < end_sleep_time)
		usleep(1000);
}

void	think(t_philo *philo)
{
	long	time_to_think;
	size_t	end_think_time;

	print(philo, THINK);
	time_to_think = (long)(philo->table->time_to_die
			- (long)(get_current_time(philo) - (long)philo->last_meal_time)
			- (long)philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		return ;
	if (time_to_think > 500)
		time_to_think = 500;
	end_think_time = get_current_time(philo) + time_to_think;
	while (get_current_time(philo) < end_think_time)
		usleep(1000);
}
