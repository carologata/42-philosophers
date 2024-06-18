/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:21:20 by cogata            #+#    #+#             */
/*   Updated: 2024/06/18 12:18:38 by cogata           ###   ########.fr       */
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

	
	sem_wait(philo->table->sem_forks);
	print(philo, FORK);
	monitor(philo);
	sem_wait(philo->table->sem_forks);
	print(philo, FORK);
	
	end_meal_time = get_current_time(philo) + philo->table->time_to_eat;
	philo->last_meal_time = get_current_time(philo);
	print(philo, EAT);
	
	while (get_current_time(philo) < end_meal_time && monitor(philo))
		usleep(1000);
	
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
		
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->number_of_meals)
	{
		// printf("id: %d, ready to post!\n", philo->id);
        sem_post(philo->table->sem_is_full[philo->id - 1]);
		// printf("id: %d, meals eaten: %zu, post!\n", philo->id, philo->meals_eaten);
	}
}

void	sleep_philo(t_philo *philo)
{
	size_t	end_sleep_time;

	monitor(philo);
	end_sleep_time = get_current_time(philo) + philo->table->time_to_sleep;
	print(philo, SLEEP);
	while (get_current_time(philo) < end_sleep_time && monitor(philo))
		usleep(1000);
}

void	think(t_philo *philo)
{
	long	time_to_think;
	size_t	end_think_time;

	monitor(philo);
	time_to_think = (long)(philo->table->time_to_die - (long)(get_current_time(philo) - (long)philo->last_meal_time) - (long)philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		return ;
	if (time_to_think > 500)
		time_to_think = 500;
	end_think_time = get_current_time(philo) + time_to_think;
	print(philo, THINK);
	while (get_current_time(philo) < end_think_time && monitor(philo))
		usleep(1000);
}
