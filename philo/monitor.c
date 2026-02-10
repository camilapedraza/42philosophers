/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:07:07 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/10 21:02:05 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	should_sim_stop(t_sim *sim)
{
	bool	value;

	pthread_mutex_lock(&sim->stop_mutex);
	value = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (value);
}

static long	get_last_meal_time(t_philo *philosopher)
{
	long	time;

	pthread_mutex_lock(&philosopher->meal_mutex);
	time = philosopher->last_meal_time;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	return (time);
}

static void	handle_death(t_philo *philosopher)
{
	t_sim	*sim;

	sim = philosopher->sim;
	pthread_mutex_lock(&sim->stop_mutex);
	if (!sim->stop)
	{
		sim->stop = true;
		pthread_mutex_unlock(&sim->stop_mutex);
		print_status(philosopher, DEAD);
	}
	else
		pthread_mutex_unlock(&sim->stop_mutex);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philosophers;
	t_sim	*sim;
	int		i;
	long	now;
	long	last_meal;

	philosophers = (t_philo *)arg;
	sim = philosophers[0].sim;
	while (1)
	{
		i = 0;
		while (i < sim->nb_philos)
		{
			last_meal = get_last_meal_time(&philosophers[i]);
			now = get_time_ms();
			if (now - last_meal >= sim->time_to_die)
			{
				handle_death(&philosophers[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
