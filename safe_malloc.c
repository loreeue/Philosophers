/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:30:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/21 11:39:15 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Performs a safe malloc and returns a pointer to the allocated memory.
*/
void	*safe_malloc(size_t bytes)
{
	void	*s;

	s = malloc(bytes);
	if (s == NULL)
	{
		printf("Error en el malloc");
		return (NULL);
	}
	return (s);
}
