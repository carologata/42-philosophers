/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:48:14 by cogata            #+#    #+#             */
/*   Updated: 2024/06/19 17:21:48 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define GRE "\033[1;32m" /* Bold Green */
# define YEL "\033[1;33m" /* Bold Yellow */
# define BLU "\033[1;34m" /* Bold Blue */
# define MAG "\033[1;35m" /* Bold Magenta */

# define FORKS "forks"
# define DEAD "dead"
# define FULL "full"
# define DINNER "dinner_finished"
# define DOOR "door"
# define KILL "kill"

# define CHILD "child"
# define PRINT "print"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	size_t				last_meal_time;
	size_t				meals_eaten;
	sem_t				*sem_philo;
	sem_t				*sem_print;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				number_of_meals;
	size_t				start_time;
	bool				dinner_finished;
	int					*pid;
	pthread_t			monitor_philos_full;
	pthread_t			monitor_philo_died;
	sem_t				*sem_forks;
	sem_t				*sem_is_dead;
	sem_t				*sem_is_full;
	sem_t				*sem_dinner_finished;
	sem_t				*sem_door;
	sem_t				*sem_kill;
}						t_table;

typedef enum e_condition
{
	DIED,
	FORK,
	EAT,
	SLEEP,
	THINK,
}						t_condition;

/* validate */
void					check_sign(char *argv[], int i, int *j, bool *sign);
void					check_zero(int argc, char *argv[]);
void					check_size(char *str);
void					validate_arguments(int argc, char *argv[]);

/* init table */
sem_t					*init_sem(char *file, int value);
void					init_table(int argc, char *argv[], t_table *table);

/* child processes */
void					start_child_process(t_table *table, int i);
void					init_philo(t_philo *philo, t_table *table, int i);
void					create_thread_for_child(t_philo *philo);
void					*monitor_last_meal(void *arg);

/* meal alone */
int						meal_alone(t_table *table);

/* meal */
void					start_meal(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);

/* safe functions */
bool					get_status(sem_t *sem, bool *variable);
void					set_status(sem_t *sem, bool *variable, bool update);
size_t					get_units(sem_t *sem, size_t *variable);
void					set_units(sem_t *sem, size_t *variable, size_t update);

/* parent monitors */
void					*monitor_last_meals(void *arg);
void					*monitor_someone_died(void *arg);
void					kill_philos(t_table *table);

/* print */
void					print(t_philo *philo, t_condition condition);

/* time */
size_t					get_time_in_ms(void);
size_t					get_current_time(t_philo *philo);

/* utils */
void					error_exit(char *error);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlen(const char *s);
size_t					ft_long_atoi(const char *nptr);

/* finish */
void					finish(int argc, t_table *table);

#endif