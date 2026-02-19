/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:21:49 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/19 18:17:46 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	should_sim_stop(t_sim *sim)
{
	bool	value;

	pthread_mutex_lock(&sim->stop_mutex);
	value = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (value);
}

static void	take_forks(t_philo *philosopher)
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

static void	release_forks(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);
}

static void	eat(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->last_meal_time = get_time_ms();
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	print_status(philosopher, EATING);
	precise_sleep(philosopher->sim->time_to_eat);
}

void	*philo_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	if (philosopher->sim->nb_philos == 1)
	{
		print_status(philosopher, TAKEN_FORK);
		usleep(to_usec(philosopher->sim->time_to_die));
		return (NULL);
	}
	if (philosopher->id % 2 == 0)
		precise_sleep(1);
	while (!should_sim_stop(philosopher->sim))
	{
		take_forks(philosopher);
		eat(philosopher);
		release_forks(philosopher);
		print_status(philosopher, SLEEPING);
		precise_sleep(philosopher->sim->time_to_sleep);
		print_status(philosopher, THINKING);
		precise_sleep(1);
	}
	return (NULL);
}
