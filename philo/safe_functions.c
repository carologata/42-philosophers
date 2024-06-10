/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:23 by cogata            #+#    #+#             */
/*   Updated: 2024/06/10 18:35:53 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_printf(t_philo *philo, t_condition condition)
{
	pthread_mutex_lock(&philo->table->mutex_print);
	if (condition == FORK)
	{
		printf("%zu %d has taken a fork\n", get_current_time(philo->table),
				philo->id);
	}
	else if (condition == EAT)
	{
		printf("%zu %d is eating\n", get_current_time(philo->table), philo->id);
	}
	else if (condition == SLEEP)
	{
		printf("%zu %d is sleeping\n", get_current_time(philo->table),
				philo->id);
	}
	else if (condition == THINK)
	{
		printf("%zu %d is thinking\n", get_current_time(philo->table),
				philo->id);
	}
	else if (condition == DIED)
	{
		printf("%zu %d died\n", get_current_time(philo->table), philo->id);
	}
	pthread_mutex_unlock(&philo->table->mutex_print);
}
