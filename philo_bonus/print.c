/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:57:30 by cogata            #+#    #+#             */
/*   Updated: 2024/06/14 16:55:29 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print(t_philo *philo, t_condition condition)
{
	monitor(philo);
	if (condition == FORK)
		printf(GRE "%zu %d has taken a fork" RST "\n", get_current_time(philo->table), philo->id);
	else if (condition == EAT)
		printf(MAG "%zu %d is eating" RST "\n", get_current_time(philo->table), philo->id);
	else if (condition == SLEEP)
		printf(BLU "%zu %d is sleeping" RST "\n", get_current_time(philo->table), philo->id);
	else if (condition == THINK)
		printf(YEL "%zu %d is thinking" RST "\n", get_current_time(philo->table), philo->id);
	else if (condition == DIED)
		printf(RED "%zu %d died" RST "\n", get_current_time(philo->table), philo->id);
}
