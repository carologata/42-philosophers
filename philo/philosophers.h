/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:48:14 by cogata            #+#    #+#             */
/*   Updated: 2024/06/08 16:16:24 by cogata           ###   ########.fr       */
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
	size_t				timestamp_last_meal;
	pthread_t			thread;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_print_fork;
	pthread_mutex_t		mutex_print_eat;
	pthread_mutex_t		mutex_print_sleep;
	pthread_mutex_t		mutex_print_think;
	pthread_mutex_t		mutex_print_die;
	bool				all_seat;
	size_t				start_time;
	bool				philo_died;
}						t_table;

typedef enum e_condition
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}						t_condition;

//init
void					validate_arguments(int argc, char *argv[]);
void					init_data(t_table *table, t_philo **philos, int argc,
							char *argv[]);
void					create_philos(t_table *table, t_philo *philos);
void					philos_ready(t_table *table);
void					wait_philos(t_table *table, t_philo *philos);

//meal functions
void					*start_meal(void *arg);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);

//time
size_t					get_time_in_ms(void);
size_t get_current_time(t_table *table);

//safe functions
void					safe_printf(t_philo *philo, t_condition condition);

//utils
void					error_exit(char *error);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlen(const char *s);
size_t					ft_long_atoi(const char *nptr);

#endif