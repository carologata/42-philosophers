/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:12:24 by cogata            #+#    #+#             */
/*   Updated: 2024/06/19 12:02:36 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	get_status(sem_t *sem, bool *variable)
{
	bool	status;

	sem_wait(sem);
	status = *variable;
	sem_post(sem);
	return (status);
}

void	set_status(sem_t *sem, bool *variable, bool update)
{
	sem_wait(sem);
	*variable = update;
	sem_post(sem);
}

size_t	get_units(sem_t *sem, size_t *variable)
{
	size_t	units;

	sem_wait(sem);
	units = *variable;
	sem_post(sem);
	return (units);
}

void	set_units(sem_t *sem, size_t *variable, size_t update)
{
	sem_wait(sem);
	*variable = update;
	sem_post(sem);
}
