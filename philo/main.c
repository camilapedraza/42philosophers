/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/13 18:04:23 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

//TODO remove EXIT functions everywhere

#include "philosophers.h"

void	exit_simulation(t_sim *sim, t_philo *philosophers, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
		pthread_mutex_destroy(&sim->forks[i++]);
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	free(sim->forks);
	free(philosophers);
	free(threads);
}

int	init_threads(t_sim *sim, t_philo *philosophers, pthread_t **threads)
{
	int	i;

	*threads = malloc(sizeof(pthread_t) * sim->nb_philos);
	if (!*threads)
		return (FAILURE);
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_create(&(*threads)[i], NULL, philo_routine, &philosophers[i]);
		i++;
	}
	return (SUCCESS);
}

int	init_philosophers(t_sim *sim, t_philo **philosophers)
{
	int	i;

	*philosophers = malloc(sizeof(t_philo) * sim->nb_philos);
	if (!*philosophers)
		return (FAILURE);
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

int	init_simulation(t_sim *sim, int ac, char **av)
{
	int	i;

	if (!parse_args(sim, ac, av))
		return (FAILURE);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philos);
	if (!sim->forks)
		return (FAILURE);
	sim->start_time = get_time_ms();
	sim->stop = false;
	i = 0;
	while (i < sim->nb_philos)
		pthread_mutex_init(&sim->forks[i++], NULL);
	pthread_mutex_init(&sim->stop_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
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
		return (1);
	}
	if (!init_simulation(&sim, ac, av))
		exit(EXIT_FAILURE);
	if (!init_philosophers(&sim, &philosophers))
		exit(EXIT_FAILURE);
	if (!init_threads(&sim, philosophers, &threads))
		exit(EXIT_FAILURE);
	pthread_create(&monitor, NULL, monitor_routine, philosophers);
	pthread_detach(monitor);
	i = 0;
	while (i < sim.nb_philos)
		pthread_join(threads[i++], NULL);
	exit_simulation(&sim, philosophers, threads);
	return (0);
}
