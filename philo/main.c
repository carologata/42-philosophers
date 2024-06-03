/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/03 18:01:41 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	int				start_time;
	struct timeval	tv;

	start_time = gettimeofday(&tv, NULL);
	if (start_time == -1)
		exit(1);
	while (gettimeofday(&tv, NULL) < start_time + philo->time_to_eat)
		usleep(philo->time_to_eat);
}

void	*live(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number_of_philosophers % 2 == 0 && philo->id % 2 == 0)
		usleep(1000);
	else if (philo->number_of_philosophers % 2 != 0 && philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex_fork[philo->id -1]);
		philo->forks[philo->id] = 1;
		if (philo->id == 0)
			philo->forks[philo->number_of_philosophers] = 1;
		else
			philo->forks[philo->id - 1] = 1;
		eat(philo);
		pthread_mutex_unlock(&philo->mutex_fork[philo->id -1]);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int i;
	t_philo philo;
	pthread_t philosohers[200];

	if (argc < 5 || argc > 6)
		printf("Number of arguments is incorret");

	philo.number_of_philosophers = ft_long_atoi(argv[1]);
	philo.time_to_die = ft_long_atoi(argv[2]);
	philo.time_to_eat = ft_long_atoi(argv[3]);
	philo.time_to_sleep = ft_long_atoi(argv[4]);
	philo.number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		philo.number_of_times_each_philosopher_must_eat = ft_long_atoi(argv[4]);

	philo.forks = malloc(philo.number_of_philosophers * sizeof(int));
	philo.mutex_fork = malloc(philo.number_of_philosophers
			* sizeof(pthread_mutex_t));
	i = 0;
	while (i < philo.number_of_philosophers)
	{
		philo.forks[i] = 0;
		pthread_mutex_init(&philo.mutex_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo.number_of_philosophers)
	{
		philo.id = i + 1;
		pthread_create(&philosohers[i], NULL, live, &philo);
		i++;
	}
}