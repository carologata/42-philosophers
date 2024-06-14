/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/14 18:43:13 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitor_last_meal(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		printf("id: %d wait\n", i + 1);
		sem_wait(table->sem_is_full[i]);
		printf("id: %d wait ok\n", i + 1);
		i++;
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		kill(table->pid[i], SIGKILL);
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int			i;
	int			status;
	t_philo		philo;
	t_table		table;
	pthread_t	monitor_full;

	init_table(argc, argv, &table);
	
	if(argc == 6)
		pthread_create(&monitor_full, NULL, monitor_last_meal, &table);
	
	table.pid = malloc(table.number_of_philosophers * sizeof(int));
	i = 0;
	while (i < table.number_of_philosophers)
	{
		table.pid[i] = fork();
		if (table.pid[i] == 0)
		{
			init_philo(&philo, &table, i);
			start_meal(&philo);
		}
		i++;
	}
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		printf("FINISHED BY THREAD\n");
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == DEAD)
	{
		i = 0;
		while (i < table.number_of_philosophers)
		{
			kill(table.pid[i], SIGKILL);
			i++;
		}
	}
	if(argc == 6)
		pthread_join(monitor_full, NULL);
}
