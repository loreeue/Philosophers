/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:23:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/06 18:23:06 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Converts input arguments to numeric values ​​and stores them in the
table structure.

Converts times to microseconds (* 1000).
Checks that these values ​​are not less than 60ms.
*/
int	parse_input(t_table *table, char *argv[], int argc)
{
	table->num_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->num_of_philos == -2 || table->time_to_die == -2
		|| table->time_to_eat == -2 || table->time_to_sleep == -2)
		return (-1);
	table->time_to_die *= 1000;
	table->time_to_eat *= 1000;
	table->time_to_sleep *= 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		return (printf("Los valores no pueden ser menores de 60ms"), -1);
	if (argc == 6)
		table->limit_of_meals = ft_atol(argv[5]);
	else
		table->limit_of_meals = -1;
	if (table->limit_of_meals == -2)
		return (-1);
	return (0);
}
