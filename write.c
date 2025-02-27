/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:53:37 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/10 18:53:39 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Write the state of each philo by locking and unlocking the write mutex.
Elapsed is "tiempo transcurrido".
*/
void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = (get_time(MILISECOND) - philo->table->start_simulation);
	if (philo->ate_already)
		return ;
	mutex_handle(&philo->table->mutex_write, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !is_simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !is_simulation_finished(philo->table))
		printf("\033[35m%-6ld %d is eating\033[0m\n", elapsed, philo->id);
	else if (status == SLEEPING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("\033[31m%-6ld %d died\033[0m\n", elapsed, philo->id);
	mutex_handle(&philo->table->mutex_write, UNLOCK);
}
