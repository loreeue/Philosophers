/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:11:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/06 18:11:40 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Validates the input, initializes the simulation, runs it, and then
cleans the resources before finishing.

usleep uses microsec, so they have to be converted to milliseconds,
which is what comes as an argument and what I have to display when running it

The clean is done when a blade dies or all have been eaten that number of times
*/
int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argv, argc) == -1)
			return (1);
		if (table_init(&table) == 1)
			return (1);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		printf("Entrada incorrecta\nUso correcto:\
			./philo 5 800 200 200 [5]");
		return (1);
	}
}
