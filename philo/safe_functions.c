/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:23 by cogata            #+#    #+#             */
/*   Updated: 2024/06/08 15:34:24 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void safe_printf(t_philo *philo, t_condition condition)
{
    if(condition == FORK)
    {
        pthread_mutex_lock(&philo->table->mutex_print_fork);
        printf("%zu %d has taken a fork\n", get_current_time(philo->table), philo->id);
        pthread_mutex_unlock(&philo->table->mutex_print_fork);
    }
    else if(condition == EAT)
    {
        pthread_mutex_lock(&philo->table->mutex_print_eat);
        printf("%zu %d is eating\n", get_current_time(philo->table), philo->id);
        pthread_mutex_unlock(&philo->table->mutex_print_eat);
    }
    else if(condition == SLEEP)
    {
        pthread_mutex_lock(&philo->table->mutex_print_sleep);
        printf("%zu %d is sleeping\n", get_current_time(philo->table), philo->id);
        pthread_mutex_unlock(&philo->table->mutex_print_sleep);
    }
    else if(condition == THINK)
    {
        pthread_mutex_lock(&philo->table->mutex_print_think);
        printf("%zu %d is thinking\n", get_current_time(philo->table), philo->id);
        pthread_mutex_unlock(&philo->table->mutex_print_think);
    }
}
