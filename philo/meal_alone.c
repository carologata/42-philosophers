/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_alone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:27:30 by cogata            #+#    #+#             */
/*   Updated: 2024/06/12 15:42:37 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_meal_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->mutex_fork[philo->fork_right]);
	safe_printf(philo, FORK);
	usleep(philo->table->time_to_die * 1000);
	pthread_mutex_unlock(&philo->table->mutex_fork[philo->fork_right]);
	safe_printf(philo, DIED);
	return (NULL);
}
