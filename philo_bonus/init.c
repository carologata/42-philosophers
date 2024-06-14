/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:46:18 by cogata            #+#    #+#             */
/*   Updated: 2024/06/14 17:05:39 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_table(int argc, char *argv[], t_table *table)
{
	int		i;
	char	*sem_full_name;

	table->number_of_philosophers = (int)ft_long_atoi(argv[1]);
	table->time_to_die = ft_long_atoi(argv[2]);
	table->time_to_eat = ft_long_atoi(argv[3]);
	table->time_to_sleep = ft_long_atoi(argv[4]);
	table->number_of_meals = 0;
	if (argc == 6)
		table->number_of_meals = ft_long_atoi(argv[5]);
	sem_unlink(FORKS);
	table->sem_forks = sem_open(FORKS, O_CREAT, 0664, table->number_of_philosophers);
	if (table->sem_forks == SEM_FAILED)
		error_exit("Semaphore error.");
	i = 0;
	while (i < table->number_of_philosophers)
	{
		sem_full_name = ft_strjoin(FULL, ft_itoa(i));
		sem_unlink(sem_full_name);
		table->sem_is_full[i] = sem_open(sem_full_name, O_CREAT, 0664, 0);
		if (table->sem_is_full[i] == SEM_FAILED)
			error_exit("Semaphore error.");
		i++;
	}
	table->start_time = get_time_in_ms();
}

void	init_philo(t_philo *philo, t_table *table, int i)
{
	philo->id = i;
	philo->last_meal_time = 0;
	philo->meals_eaten = 0;
	philo->table = table;
}
