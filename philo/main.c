/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/05 18:25:01 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	validate_arguments(int argc, char *argv[])
{
	int		i;
	int		j;
	bool	sign;
	int		len;

	if (argc < 5 || argc > 6)
		error_exit("Invalid number of arguments.");
	i = 1;
	sign = false;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
		{
			sign = true;
			if (argv[i][j] == '-')
				error_exit("Invalid negative number.");
			else
				j++;
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				error_exit("Invalid number.");
			j++;
		}
		len = ft_strlen(argv[i]);
		if ((len > 19 && !sign) || (len > 20 && sign) || (len == 19
				&& ft_strcmp(&argv[i][0], "9223372036854775807") > 0 && !sign)
			|| (len == 20 && ft_strcmp(&argv[i][1], "9223372036854775807") > 0
				&& sign))
			error_exit("Argument is too big");
		i++;
	}
}

void	init_data(t_table *table, t_philo **philos, int argc, char *argv[])
{
	int	i;

	table->number_of_philosophers = ft_long_atoi(argv[1]);
	table->time_to_die = ft_long_atoi(argv[2]);
	table->time_to_eat = ft_long_atoi(argv[3]);
	table->time_to_sleep = ft_long_atoi(argv[4]);
	table->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_long_atoi(argv[5]);
	table->mutex_fork = malloc(table->number_of_philosophers * sizeof(pthread_mutex_t));
	*philos = malloc(table->number_of_philosophers * sizeof(t_philo));
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
	table->all_seat = false;
	table->start_time = 0;
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

void philos_ready(t_table *table)
{
	table->all_seat = true;
}

void wait_philos(t_table *table, t_philo *philos)
{
	int i = 0;
	while(i < table->number_of_philosophers)
	{
		pthread_join(philos->thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo *philos;

	//VALIDATE ARGUMENTS
	validate_arguments(argc, argv);
	
	//GET ARGUMENTS AND INIT DATA
	init_data(&table, &philos, argc, argv);
	
	//GET START TIME
	table.start_time = get_time_in_ms(); 
	
	//START THREADS
	create_philos(&table, philos);
	
	//WAIT PHILOSOPHERS TO SEAT
	philos_ready(&table);
	
	//WAIT THEM TO EXIT
	wait_philos(&table, philos);
}
