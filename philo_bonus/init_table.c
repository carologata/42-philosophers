/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:46:18 by cogata            #+#    #+#             */
/*   Updated: 2024/06/20 11:11:34 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

sem_t	*init_sem(char *file, int value)
{
	sem_t	*sem;

	sem_unlink(file);
	sem = sem_open(file, O_CREAT, 0664, value);
	sem_unlink(file);
	if (sem == SEM_FAILED)
		error_exit("Semaphore error.");
	return (sem);
}

void	init_table(int argc, char *argv[], t_table *table)
{
	table->number_of_philosophers = (int)ft_long_atoi(argv[1]);
	table->time_to_die = ft_long_atoi(argv[2]);
	table->time_to_eat = ft_long_atoi(argv[3]);
	table->time_to_sleep = ft_long_atoi(argv[4]);
	table->number_of_meals = 0;
	if (argc == 6)
		table->number_of_meals = ft_long_atoi(argv[5]);
	if (table->number_of_philosophers > 1)
	{
		table->dinner_finished = false;
		table->sem_door = init_sem(DOOR, table->number_of_philosophers / 2);
		table->sem_forks = init_sem(FORKS, table->number_of_philosophers);
		table->sem_is_dead = init_sem(DEAD, 0);
		table->sem_is_full = init_sem(FULL, 0);
		table->sem_dinner_finished = init_sem(DINNER, 1);
		table->sem_kill = init_sem(KILL, 1);
		pthread_create(&(table->monitor_philo_died), NULL, monitor_someone_died,
			table);
		if (argc == 6)
			pthread_create(&(table->monitor_philos_full), NULL,
				monitor_last_meals, table);
	}
	table->start_time = get_time_in_ms();
}
