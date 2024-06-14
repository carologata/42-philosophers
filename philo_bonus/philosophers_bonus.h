/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:48:14 by cogata            #+#    #+#             */
/*   Updated: 2024/06/14 16:53:18 by cogata           ###   ########.fr       */
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
# define FULL "full"
# define DEAD 1

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	size_t				last_meal_time;
	size_t				meals_eaten;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t					number_of_meals;
	size_t				start_time;
	int					*pid;
	sem_t				*sem_forks;
	sem_t				**sem_is_full;
}						t_table;

typedef enum e_condition
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
}						t_condition;

/* validate */
void					check_sign(char *argv[], int i, int *j, bool *sign);
void					check_zero(int argc, char *argv[]);
void					validate_arguments(int argc, char *argv[]);
void					init_data(t_table *table, t_philo **philos, int argc,
							char *argv[]);
void					init_philos_mutexes(t_table *table, t_philo **philos);
void					create_philos(t_table *table, t_philo *philos);
void					philos_ready(t_table *table);
void					wait_philos(t_table *table, t_philo *philos);
void					free_mem_philos(t_philo *philos, t_table *table);

/* init */
void					init_table(int argc, char *argv[], t_table *table);
void					init_philo(t_philo *philo, t_table *table, int i);

/* monitor thread full */
void					*monitor_last_meal(void *arg);

/* meal */
void					start_meal(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);

/* monitor dead */
bool					monitor(t_philo *philo);

/* time */
size_t					get_time_in_ms(void);
size_t					get_current_time(t_table *table);

/* print */
void					print(t_philo *philo, t_condition condition);

/* utils */
void					error_exit(char *error);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlen(const char *s);
size_t					ft_long_atoi(const char *nptr);
char					*ft_copy_str(char const *s1, char const *s2, char *res);
char					*ft_strjoin(char const *s1, char const *s2);
long long				ft_count_divider(long nb);
char					*ft_init_str(long nb, char *res, int count,
							int is_negative);
int						ft_count_num(long nb);
char					*ft_itoa(int n);

#endif