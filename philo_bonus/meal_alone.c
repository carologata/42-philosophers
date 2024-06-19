/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_alone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:34:35 by cogata            #+#    #+#             */
/*   Updated: 2024/06/19 17:23:14 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	meal_alone(t_table *table)
{
	int		pid;
	int		status;
	t_philo	philo;

	pid = fork();
	if (pid == 0)
	{
		init_philo(&philo, table, 0);
		print(&philo, FORK);
		usleep(philo.table->time_to_die * 1000);
		print(&philo, DIED);
		sem_close(philo.sem_print);
	}
	waitpid(pid, &status, 0);
	return (0);
}
