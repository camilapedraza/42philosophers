/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:21:49 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/10 21:03:17 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philosopher)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

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
	print_status(philosopher, TAKEN_FORK);
	pthread_mutex_lock(second);
	print_status(philosopher, TAKEN_FORK);
}

void	release_forks(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);
}

void	eat(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->last_meal_time = get_time_ms();
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	print_status(philosopher, EATING);
	usleep(to_usec(philosopher->sim->time_to_eat));
}

void	*philo_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (!should_sim_stop(philosopher->sim))
	{
		take_forks(philosopher);
		eat(philosopher);
		release_forks(philosopher);
		print_status(philosopher, SLEEPING);
		usleep(200000);
		print_status(philosopher, THINKING);
	}
	return (NULL);
}
