/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:05:24 by cogata            #+#    #+#             */
/*   Updated: 2024/06/18 12:20:33 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	monitor(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (get_current_time(philo) > philo->last_meal_time + philo->table->time_to_die)
	{
		// printf("id: %d, current time: %zu, last meal: %zu, time to die: %zu\n", philo->id, get_current_time(philo), philo->last_meal_time, philo->table->time_to_die);
		print(philo, DIED);
		exit(DEAD);
	}	
	return (true);
}