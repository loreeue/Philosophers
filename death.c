/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:02:48 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/21 11:38:33 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Checks if the simulation has ended.

Gets the boolean of end_simulation with a mutex.
*/
bool	is_simulation_finished(t_table *table)
{
	return (get_bool(&table->mutex_table, &table->end_simulation));
}

/*
Checks if an philo has died.

First, check if the philo has already eaten the required number of times
(ate_already), and if so, return false because it cannot starve.

If the elapsed time (elapsed) is greater than the maximum time it can go
without eating (time_to_die), return true, indicating that the philo has
died.

Otherwise, return false, indicating that the philo has not died.
*/
bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->mutex_philo, &philo->ate_already))
		return (false);
	elapsed = get_time(MILISECOND) - get_long(&philo->mutex_philo,
			&philo->time_from_last_meal);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}
