/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:05:25 by cogata            #+#    #+#             */
/*   Updated: 2024/06/08 16:16:43 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_table *table, t_philo **philos, int argc, char *argv[])
{
	int	i;

	table->number_of_philosophers = (int)ft_long_atoi(argv[1]);
	table->time_to_die = ft_long_atoi(argv[2]);
	table->time_to_eat = ft_long_atoi(argv[3]);
	table->time_to_sleep = ft_long_atoi(argv[4]);
	table->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_long_atoi(argv[5]);
	*philos = malloc(table->number_of_philosophers * sizeof(t_philo));
	table->mutex_fork = malloc(table->number_of_philosophers * sizeof(pthread_mutex_t));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].fork_left = i;
		(*philos)[i].fork_right = (*philos)[i].id % table->number_of_philosophers;
		(*philos)[i].table = table;
		pthread_mutex_init(&table->mutex_fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->mutex_print_fork, NULL);
	pthread_mutex_init(&table->mutex_print_eat, NULL);
	pthread_mutex_init(&table->mutex_print_sleep, NULL);
	pthread_mutex_init(&table->mutex_print_think, NULL);
	pthread_mutex_init(&table->mutex_print_die, NULL);
	table->all_seat = false;
	table->start_time = 0;
	table->philo_died = false;
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
}

/* void	philos_ready(t_table *table)
{
	pthread_mutex_lock(&table->mutex_general);
	table->all_seat = true;
	pthread_mutex_unlock(&table->mutex_general);
} */
