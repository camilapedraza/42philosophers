/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:03:07 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/16 20:00:05 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_sim *sim, t_philo *philos, pthread_t **threads)
{
	int	i;

	*threads = malloc(sizeof(pthread_t) * sim->nb_philos);
	if (!*threads)
	{
		cleanup_philosophers(&philos, sim->nb_philos);
		cleanup_sim(sim, sim->nb_philos);
		return (FAILURE);
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		if (pthread_create(&(*threads)[i], NULL, philo_routine, &philos[i]))
		{
			cleanup_threads(threads, i);
			cleanup_philosophers(&philos, sim->nb_philos);
			cleanup_sim(sim, sim->nb_philos);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_mutex_meal(t_philo **philosophers, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		if (pthread_mutex_init(&(*philosophers)[i].meal_mutex, NULL))
		{
			cleanup_philosophers(philosophers, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_philosophers(t_sim *sim, t_philo **philosophers)
{
	int	i;

	*philosophers = malloc(sizeof(t_philo) * sim->nb_philos);
	if (!*philosophers)
	{
		cleanup_sim(sim, sim->nb_philos);
		return (FAILURE);
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		(*philosophers)[i].sim = sim;
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].last_meal_time = sim->start_time;
		(*philosophers)[i].meals_eaten = 0;
		(*philosophers)[i].fork_left = &sim->forks[i];
		(*philosophers)[i].fork_right = &sim->forks[(i + 1) % sim->nb_philos];
		i++;
	}
	if (!init_mutex_meal(philosophers, sim->nb_philos))
	{
		cleanup_sim(sim, sim->nb_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_mutex_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
		{
			cleanup_forks(sim, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_simulation(t_sim *sim, int ac, char **av)
{
	if (!parse_args(sim, ac, av))
		return (FAILURE);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philos);
	if (!sim->forks)
		return (FAILURE);
	sim->start_time = get_time_ms();
	sim->stop = false;
	if (!init_mutex_forks(sim))
		return (FAILURE);
	if (pthread_mutex_init(&sim->stop_mutex, NULL))
	{
		cleanup_forks(sim, sim->nb_philos);
		return (FAILURE);
	}
	if (pthread_mutex_init(&sim->print_mutex, NULL))
	{
		pthread_mutex_destroy(&sim->stop_mutex);
		cleanup_forks(sim, sim->nb_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}
