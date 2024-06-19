/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:15:51 by cogata            #+#    #+#             */
/*   Updated: 2024/06/19 16:30:57 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	finish(int argc, t_table *table)
{
	pthread_join(table->monitor_philo_died, NULL);
	if (argc == 6)
		pthread_join(table->monitor_philos_full, NULL);
	sem_close(table->sem_door);
	sem_close(table->sem_forks);
	sem_close(table->sem_is_dead);
	sem_close(table->sem_is_full);
	sem_close(table->sem_dinner_finished);
	sem_close(table->sem_kill);
	free(table->pid);
}
