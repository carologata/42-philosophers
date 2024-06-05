/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:48:14 by cogata            #+#    #+#             */
/*   Updated: 2024/06/05 18:20:08 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					fork_left;
	int					fork_right;
	pthread_t			thread;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	pthread_mutex_t		*mutex_fork;
	bool				all_seat;
	size_t				start_time;
}						t_table;

void					validate_arguments(int argc, char *argv[]);
void					init_data(t_table *table, t_philo **philos, int argc,
							char *argv[]);
void					create_philos(t_table *table, t_philo *philos);
void					philos_ready(t_table *table);
void					*start_meal(void *arg);
void					wait_philos(t_table *table, t_philo *philos);

size_t					get_time_in_ms(void);
size_t					get_current_time(size_t start_time);

//utils
void					error_exit(char *error);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlen(const char *s);
long					ft_long_atoi(const char *nptr);

#endif