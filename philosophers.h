/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:16:43 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/10 15:16:50 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
usleep is in unistd
Threads are in pthread
Mutexes are in pthread
Struct timeval is in sys/time
*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// CONSTANTS
typedef enum e_flags
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_flags;

typedef enum e_time
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

// STRUCTURES
typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

/*
num_of_meals: number of times you have eaten
ate_already: when you reached the maximum number of meals
time_from_last_meal: the time that has passed
	since you last ate
*/
typedef struct s_philo
{
	int				id;
	long			num_of_meals;
	bool			ate_already;
	long			time_from_last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	mutex_philo;
	t_table			*table;
}	t_philo;

/*
limit_of_meals: number of meals you can make -> -1 if you don't get in
start_simulation: simulation start time
end_simulation: when an philo dies or the minimum number of meals is reached
all_threads_ready: to synchronize philos
num_of_threads_running: number of threads that are running
thread_monitor: thread for the monitor
*/
struct s_table
{
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			limit_of_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			all_threads_ready;
	long			num_of_threads_running;
	pthread_t		thread_monitor;
	pthread_mutex_t	mutex_table;
	pthread_mutex_t	mutex_write;
	t_fork			*array_forks;
	t_philo			*array_philos;
};

// ACTIONS
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		precise_usleep(long usec, t_table *table);
void		clean(t_table *table);

// DEATH
bool		is_simulation_finished(t_table *table);
bool		philo_died(t_philo *philo);

// DINNER
void		dinner_start(t_table *table);

// HANDLE
void		mutex_handle(pthread_mutex_t *mutex, t_flags f);
void		thread_handle(pthread_t *thread, void *(*foo)(void *),
				void *data, t_flags f);

// INIT
int			table_init(t_table *table);

// PARSING
int			parse_input(t_table *table, char *argv[], int argc);

// SAFE_MALLOC
void		*safe_malloc(size_t bytes);

// SYNCHRO
void		wait_all_threads(t_table *table);
bool		all_threads_running(pthread_mutex_t *mutex,
				long *threads, long philo_nbr);

// UTILS
long		get_time(t_time time);
long		ft_atol(const char *s);

// VALUES
void		set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool		get_bool(pthread_mutex_t *mutex, bool *value);
void		set_long(pthread_mutex_t *mutex, long *dest, long value);
long		get_long(pthread_mutex_t *mutex, long *value);
void		increase_long(pthread_mutex_t *mutex, long *value);

// WRITE
void		write_status(t_status status, t_philo *philo);

#endif
