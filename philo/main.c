/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/13 19:47:02 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

//TODO remove EXIT functions everywhere

#include "philosophers.h"

int	init_threads(t_sim *sim, t_philo *philos, pthread_t **threads)
{
	int	i;

	*threads = malloc(sizeof(pthread_t) * sim->nb_philos);
	if (!*threads)
	{
		cleanup(sim, philos, NULL);
		return (FAILURE);
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		if (pthread_create(&(*threads)[i], NULL, philo_routine, &philos[i]))
		{
			while (--i >= 0)
				pthread_join((*threads)[i], NULL);
			free(*threads);
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
		cleanup(sim, NULL, NULL);
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
		pthread_mutex_init(&(*philosophers)[i].meal_mutex, NULL);
		i++;
	}
	return (SUCCESS);
}

// TODO handle exit for all init failures
int	main(int ac, char **av)
{
	int			i;
	pthread_t	*threads;
	t_philo		*philosophers;
	t_sim		sim;
	pthread_t	monitor;

	if (ac < 5)
	{
		print_help();
		return (EXIT_FAILURE);
	}
	if (!init_simulation(&sim, ac, av))
		return (EXIT_FAILURE);
	if (!init_philosophers(&sim, &philosophers))
		return (EXIT_FAILURE);
	if (!init_threads(&sim, philosophers, &threads))
		return (EXIT_FAILURE);
	pthread_create(&monitor, NULL, monitor_routine, philosophers);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < sim.nb_philos)
		pthread_join(threads[i++], NULL);
	cleanup(&sim, philosophers, threads);
	return (EXIT_SUCCESS);
}
