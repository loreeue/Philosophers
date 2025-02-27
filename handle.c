/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:36:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/02/21 11:36:22 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Manages mutex operations based on the value of f:
	- locks
	- unlocks
	- initializes
	- destroys
*/
void	mutex_handle(pthread_mutex_t *mutex, t_flags f)
{
	if (f == LOCK)
		pthread_mutex_lock(mutex);
	else if (f == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (f == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (f == DESTROY)
		pthread_mutex_destroy(mutex);
}

/*
Manages thread operations based on the value of f:
	- create
	- wait
	- unbind
*/
void	thread_handle(pthread_t *thread, void *(*foo)(void *),
	void *data, t_flags f)
{
	if (f == CREATE)
		pthread_create(thread, NULL, foo, data);
	else if (f == JOIN)
		pthread_join(*thread, NULL);
	else if (f == DETACH)
		pthread_detach(*thread);
}
