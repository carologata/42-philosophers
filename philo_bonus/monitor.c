/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:05:24 by cogata            #+#    #+#             */
/*   Updated: 2024/06/14 16:52:07 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	monitor(t_philo *philo)
{
	int i;
	t_table *table;
	int philos_are_full;

	i = 0;
	philos_are_full = 0;
	table = philo->table;
	if (get_current_time(philo->table) > philo->last_meal_time + philo->table->time_to_die)
		exit(DEAD);
	return (true);
}