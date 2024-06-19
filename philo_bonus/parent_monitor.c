/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:47:02 by cogata            #+#    #+#             */
/*   Updated: 2024/06/19 16:24:01 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitor_last_meals(void *arg)
{
	int		philos_full;
	t_table	*table;

	table = (t_table *)arg;
	philos_full = 0;
	while (!get_status(table->sem_dinner_finished, &table->dinner_finished))
	{
		sem_wait(table->sem_is_full);
		philos_full++;
		if (philos_full == table->number_of_philosophers)
		{
			set_status(table->sem_dinner_finished, &table->dinner_finished,
				true);
			sem_wait(table->sem_kill);
			kill_philos(table);
			sem_post(table->sem_kill);
			sem_post(table->sem_is_dead);
			return (NULL);
		}
	}
	return (NULL);
}

void	*monitor_someone_died(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!get_status(table->sem_dinner_finished, &table->dinner_finished))
	{
		sem_wait(table->sem_is_dead);
		if (get_status(table->sem_dinner_finished, &table->dinner_finished))
			return (NULL);
		set_status(table->sem_dinner_finished, &table->dinner_finished, true);
		sem_wait(table->sem_kill);
		kill_philos(table);
		sem_post(table->sem_kill);
		return (NULL);
	}
	return (NULL);
}

void	kill_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		kill(table->pid[i], SIGKILL);
		i++;
	}
}
