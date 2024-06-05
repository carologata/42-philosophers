/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:05 by cogata            #+#    #+#             */
/*   Updated: 2024/06/05 18:26:16 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_left]);
    printf("%zu %d has taken a fork", get_current_time(philo->table->start_time), philo->id);
    pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_right]);
    printf("%zu %d has taken a fork", get_current_time(philo->table->start_time), philo->id);    

    printf("%zu %d is eating", get_current_time(philo->table->start_time), philo->id);    
    while(get_current_time(philo->table->start_time) < philo->table->start_time + philo->table->time_to_eat)
    {
        usleep(philo->table->time_to_eat);
    }
    
   
}

void *start_meal(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;

	while(!philo->table->all_seat)
		;
    
    while(1)
    {
        eat(philo);
        // sleep();
        // think();
    }
}