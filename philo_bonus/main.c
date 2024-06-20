/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:19 by cogata            #+#    #+#             */
/*   Updated: 2024/06/20 10:51:04 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	int		i;
	int		status;
	t_table	table;

	validate_arguments(argc, argv);
	init_table(argc, argv, &table);
	if (table.number_of_philosophers == 1)
		return (meal_alone(&table));
	table.pid = malloc(table.number_of_philosophers * sizeof(int));
	i = 0;
	sem_wait(table.sem_kill);
	while (i < table.number_of_philosophers)
	{
		table.pid[i] = fork();
		if (table.pid[i] == 0)
			start_child_process(&table, i);
		i++;
	}
	sem_post(table.sem_kill);
	i = 0;
	while (i++ < table.number_of_philosophers)
		waitpid(table.pid[i], &status, 0);
	finish(argc, &table);
	return (0);
}
