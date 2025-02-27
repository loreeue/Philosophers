/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:31:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/21 11:38:23 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
This function represents the eating action of an philo.

First, it locks the mutexes of the forks,
then it records the time since the last meal and
increments the philo's meal counter.

Next, it prints the "eating" status and waits the time
needed to complete the action.
If the philo has reached the allowed meal limit,
it is marked as having eaten enough.

Finally, it releases the mutexes of the forks.
*/
void	eat(t_philo *philo)
{
	mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->mutex_philo, &philo->time_from_last_meal,
		get_time(MILISECOND));
	philo->num_of_meals++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_of_meals > 0
		&& philo->num_of_meals == philo->table->limit_of_meals)
		set_bool(&philo->mutex_philo, &philo->ate_already, true);
	mutex_handle(&philo->first_fork->fork, UNLOCK);
	mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
Controls the thinking action of an philo.

It prints that the philo is thinking.

If the number of philos is even, the function terminates without doing
anything else.

Otherwise, it calculates a wait time and performs a precise wait.
*/
void	think(t_philo *philo)
{
	long	t_think;

	write_status(THINKING, philo);
	if (philo->table->num_of_philos % 2 == 0)
		return ;
	t_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

/*
If the waiting time is long, use usleep().

For shorter times, use a loop to ensure greater accuracy.

The function also constantly checks whether the simulation has finished
to avoid unnecessary waiting.
*/
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (is_simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

/*
It cleans up and releases the resources used in the simulation.

It loops through all the philos and destroys their mutexes.

Then, it destroys the global mutexes for the table and the write.

Finally, it frees the memory of the forks and philos.
*/
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->num_of_philos)
	{
		philo = table->array_philos + i;
		mutex_handle(&philo->mutex_philo, DESTROY);
		i++;
	}
	mutex_handle(&table->mutex_table, DESTROY);
	mutex_handle(&table->mutex_write, DESTROY);
	free(table->array_forks);
	free(table->array_philos);
}
