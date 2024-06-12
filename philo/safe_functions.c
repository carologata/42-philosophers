/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:23 by cogata            #+#    #+#             */
/*   Updated: 2024/06/12 15:43:14 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_printf(t_philo *philo, t_condition condition)
{
	if (get_status(&philo->mutex_philo, &philo->table->are_full)
		|| get_status(&philo->mutex_philo, &philo->table->is_dead))
		return ;
	pthread_mutex_lock(&philo->table->mutex_print);
	if (condition == FORK)
		printf(GRE "%zu %d has taken a fork" RST "\n",
			get_current_time(philo->table), philo->id);
	else if (condition == EAT)
		printf(MAG "%zu %d is eating" RST "\n", get_current_time(philo->table),
			philo->id);
	else if (condition == SLEEP)
		printf(BLU "%zu %d is sleeping" RST "\n",
			get_current_time(philo->table), philo->id);
	else if (condition == THINK)
		printf(YEL "%zu %d is thinking" RST "\n",
			get_current_time(philo->table), philo->id);
	else if (condition == DIED)
		printf(RED "%zu %d died" RST "\n", get_current_time(philo->table),
			philo->id);
	pthread_mutex_unlock(&philo->table->mutex_print);
}

bool	get_status(pthread_mutex_t *mutex, bool *variable)
{
	bool	status;

	pthread_mutex_lock(mutex);
	status = *variable;
	pthread_mutex_unlock(mutex);
	return (status);
}

void	set_status(pthread_mutex_t *mutex, bool *variable, bool update)
{
	pthread_mutex_lock(mutex);
	*variable = update;
	pthread_mutex_unlock(mutex);
}

size_t	get_units(pthread_mutex_t *mutex, size_t *variable)
{
	size_t	units;

	pthread_mutex_lock(mutex);
	units = *variable;
	pthread_mutex_unlock(mutex);
	return (units);
}

void	set_units(pthread_mutex_t *mutex, size_t *variable, size_t update)
{
	pthread_mutex_lock(mutex);
	*variable = update;
	pthread_mutex_unlock(mutex);
}
