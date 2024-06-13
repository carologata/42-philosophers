/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:05:25 by cogata            #+#    #+#             */
/*   Updated: 2024/06/13 16:05:04 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos_mutexes(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].fork_left = i;
		(*philos)[i].fork_right = (*philos)[i].id % table->number_of_philosophers;
		(*philos)[i].table = table;
		(*philos)[i].last_meal_time = 0;
		(*philos)[i].meals_eaten = 0;
		pthread_mutex_init(&(*philos)[i].mutex_philo, NULL);
		pthread_mutex_init(&table->mutex_fork[i], NULL);
		i++;
	}
}

void	init_data(t_table *table, t_philo **philos, int argc, char *argv[])
{
	table->number_of_philosophers = (int)ft_long_atoi(argv[1]);
	table->time_to_die = ft_long_atoi(argv[2]);
	table->time_to_eat = ft_long_atoi(argv[3]);
	table->time_to_sleep = ft_long_atoi(argv[4]);
	table->number_of_meals = -1;
	if (argc == 6)
		table->number_of_meals = ft_long_atoi(argv[5]);
	table->mutex_fork = malloc(table->number_of_philosophers
			* sizeof(pthread_mutex_t));
	*philos = malloc(table->number_of_philosophers * sizeof(t_philo));
	init_philos_mutexes(table, philos);
	pthread_mutex_init(&table->mutex_dead, NULL);
	pthread_mutex_init(&table->mutex_full, NULL);
	pthread_mutex_init(&table->mutex_print, NULL);
	table->is_dead = false;
	table->are_full = false;
	table->start_time = get_time_in_ms();
}

void	create_philos(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, start_meal, &philos[i]);
		i++;
	}
	pthread_create(&table->thread, NULL, monitor_philos, (void *)philos);
}
