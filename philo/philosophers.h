/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:48:14 by cogata            #+#    #+#             */
/*   Updated: 2024/06/11 16:44:36 by cogata           ###   ########.fr       */
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

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define GRE "\033[1;32m" /* Bold Green */
# define YEL "\033[1;33m" /* Bold Yellow */
# define BLU "\033[1;34m" /* Bold Blue */
# define MAG "\033[1;35m" /* Bold Magenta */

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					fork_left;
	int					fork_right;
	size_t				last_meal_time;
	size_t				meals_eaten;
	pthread_t			thread;
	pthread_mutex_t		mutex_philo;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				number_of_meals;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_print;
	bool				is_dead;
	bool				are_full;
	size_t				start_time;
	pthread_t			thread;
}						t_table;

typedef enum e_condition
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
	OTHER,
	OTHER2
}						t_condition;

void					validate_arguments(int argc, char *argv[]);
void					init_data(t_table *table, t_philo **philos, int argc,
							char *argv[]);
void					create_philos(t_table *table, t_philo *philos);
void					philos_ready(t_table *table);
void					wait_philos(t_table *table, t_philo *philos);
void					free_mem_philos(t_philo *philos, t_table *table);

void					*start_meal_alone(void *arg);
void					*start_meal(void *arg);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);

void					safe_printf(t_philo *philo, t_condition condition);
bool					get_status(pthread_mutex_t *mutex, bool variable);
void					set_status(pthread_mutex_t *mutex, bool *variable,
							bool upudate);
size_t					get_units(pthread_mutex_t *mutex, size_t variable);
void					set_units(pthread_mutex_t *mutex, size_t *variable,
							size_t update);

void					*monitor_philos(void *arg);

size_t					get_time_in_ms(void);
size_t					get_current_time(t_table *table);

void					error_exit(char *error);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlen(const char *s);
size_t					ft_long_atoi(const char *nptr);

#endif