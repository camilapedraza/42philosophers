/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:21:49 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/09 15:28:52 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philosopher)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philosopher->fork_left < philosopher->fork_right)
	{
		first = philosopher->fork_left;
		second = philosopher->fork_right;
	}
	else
	{
		first = philosopher->fork_right;
		second = philosopher->fork_left;
	}
	pthread_mutex_lock(first);
	print_status(philosopher, FORK);
	pthread_mutex_lock(second);
	print_status(philosopher, FORK);
}

void	release_forks(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);
}