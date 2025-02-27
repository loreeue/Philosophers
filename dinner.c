/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:33:10 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/21 12:43:34 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
When there is only one philo in the simulation.

First, it waits for all threads to be ready
it records the time of its last meal.

Then, it increments the number of running threads and
writes the "take first fork" state.

Since it cannot eat without a second fork, it enters a waiting loop
until the simulation finishes.
*/
static void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->mutex_philo, &philo->time_from_last_meal,
		get_time(MILISECOND));
	increase_long(&philo->table->mutex_table,
		&philo->table->num_of_threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while (!is_simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

/*
Simulates the dinner of each phylum when there is more than one.

First, it waits for all threads to be ready and
records the time of their last meal.

Then, it increments the running thread counter.

It enters a loop in which, as long as the simulation has not finished
and the phylum has not reached the meal limit, it performs:
- Eats.
- Changes its state to "sleeping" and waits for the sleep time.
- Then it thinks before trying to eat again.
*/
static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->mutex_philo, &philo->time_from_last_meal,
		get_time(MILISECOND));
	increase_long(&philo->table->mutex_table,
		&philo->table->num_of_threads_running);
	while (!is_simulation_finished(philo->table))
	{
		if (philo->ate_already)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}

/*
It monitors the dinner and detects if any philo dies.

First, it waits until all the threads of the philos are running.

Then, it constantly checks if any philo has died.

If an philo has died, it marks the end of the simulation and writes "dead".

The loop continues until the simulation has finished.
*/
static void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->mutex_table,
			&table->num_of_threads_running, table->num_of_philos));
	while (!is_simulation_finished(table))
	{
		i = 0;
		while (i < table->num_of_philos && !is_simulation_finished(table))
		{
			if (philo_died(table->array_philos + i))
			{
				set_bool(&table->mutex_table, &table->end_simulation, true);
				write_status(DIED, table->array_philos + i);
			}
			i++;
		}
	}
	return (NULL);
}

/*
Starts the dinner simulation.

If no meals are allowed, the function returns immediately.

If there is only one philo, a thread is created that runs one_philo().

If there are multiple philo, multiple threads are created that run
dinner_simulation().

An additional thread (monitor_dinner) is started to monitor the dinner.

The simulation is marked as being started and all threads are indicated to
be ready.

Then, wait for all philo to finish (JOIN in each thread).

Finally, indicate that the simulation is finished and end the monitor thread.
*/
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_of_meals == 0)
		return ;
	else if (table->num_of_philos == 1)
		thread_handle(&table->array_philos[0].thread_id, one_philo,
			&table->array_philos[0], CREATE);
	else
	{
		while (++i < table->num_of_philos)
			thread_handle(&table->array_philos[i].thread_id,
				dinner_simulation, &table->array_philos[i], CREATE);
	}
	thread_handle(&table->thread_monitor, monitor_dinner, table, CREATE);
	table->start_simulation = get_time(MILISECOND);
	set_bool(&table->mutex_table, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->num_of_philos)
		thread_handle(&table->array_philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->mutex_table, &table->end_simulation, true);
	thread_handle(&table->thread_monitor, NULL, NULL, JOIN);
}
