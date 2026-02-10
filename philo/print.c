/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:24:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/10 21:05:27 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*status_msg(t_status status)
{
	if (status == THINKING)
		return ("is thinking");
	if (status == SLEEPING)
		return ("is sleeping");
	if (status == EATING)
		return ("is eating");
	if (status == TAKEN_FORK)
		return ("has taken a fork");
	if (status == DEAD)
		return ("died");
	return ("");
}

void	print_status(t_philo *philosopher, t_status status)
{
	long	timestamp;

	pthread_mutex_lock(&philosopher->sim->stop_mutex);
	if (philosopher->sim->stop && status != DEAD)
	{
		pthread_mutex_unlock(&philosopher->sim->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philosopher->sim->stop_mutex);
	pthread_mutex_lock(&philosopher->sim->print_mutex);
	timestamp = timestamp_ms(philosopher->sim);
	printf("%ld %d %s\n", timestamp, philosopher->id, status_msg(status));
	pthread_mutex_unlock(&philosopher->sim->print_mutex);
}
