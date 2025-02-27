/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:28:00 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/10 15:28:02 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Assigns forks to each philo based on its position on the table.

By default, the philo takes the fork on its right first, then the one on its
left.

If the philo id is even, the order is reversed: it takes the fork on its left
first, then the one on its right.

This helps reduce the possibility of deadlocks in the simulation.
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_num;

	philo_num = philo->table->num_of_philos;
	philo->first_fork = &forks[(philo_pos + 1) % philo_num];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_num];
	}
}

/*
Initializes the philos in the simulation.

The array of philos is traversed and each philo is assigned an id,
its variables are initialized and the table is associated with it.

The mutex of each philo is initialized.

The corresponding forks are assigned.
*/
static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_of_philos)
	{
		philo = table->array_philos + i;
		philo->id = i + 1;
		philo->ate_already = false;
		philo->num_of_meals = 0;
		philo->table = table;
		mutex_handle(&philo->mutex_philo, INIT);
		assign_forks(philo, table->array_forks, i);
		i++;
	}
}

/*
Initializes the main table structure and allocates memory for the philos
and forks.

Allocates memory for the philos and initializes the mutexes.
Allocates memory for the forks and initializes them.
Initializes the philos.

Returns 0 if everything went well or 1 if there was an error.
*/
int	table_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->array_philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (table->array_philos == NULL)
		return (1);
	table->num_of_threads_running = 0;
	mutex_handle(&table->mutex_table, INIT);
	mutex_handle(&table->mutex_write, INIT);
	table->array_forks = malloc(sizeof(t_fork) * table->num_of_philos);
	if (table->array_forks == NULL)
		return (1);
	while (i < table->num_of_philos)
	{
		mutex_handle(&table->array_forks[i].fork, INIT);
		table->array_forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
	return (0);
}
