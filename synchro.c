/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/21 12:44:05 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Holds the thread on hold until all the philo threads are ready.
*/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutex_table, &table->all_threads_ready))
		;
}

/*
Checks if all threads have started correctly.

Locks the mutex to safely access the threads variable.

If the number of running threads is equal to the total number of threads,
returns true.

Unlocks the mutex before returning the result.
*/
bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
			long philo_nbr)
{
	bool	bol;

	bol = false;
	mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		bol = true;
	mutex_handle(mutex, UNLOCK);
	return (bol);
}
