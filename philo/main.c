/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/10 21:02:34 by mpedraza         ###   ########.fr       */
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

// TODO time_to_eat needs to be dynamic based on parameters
// TODO time_to_die needs to be dynamic based on parameters
int	init_simulation(t_sim *sim, int n)
{
	int	i;

	if (n <= 0)
		return (FAILURE);
	sim->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!sim->forks)
		return (FAILURE);
	sim->start_time = get_time_ms();
	sim->time_to_eat = 200;
	sim->time_to_die = 500;
	sim->nb_philos = n;
	sim->stop = false;
	i = 0;
	while (i < n)
		pthread_mutex_init(&sim->forks[i++], NULL);
	pthread_mutex_init(&sim->stop_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	return (SUCCESS);
}

// TODO guard clause for ac < 4
int	main(int ac, char **av)
{
	int			i;
	pthread_t	*threads;
	t_philo		*philosophers;
	t_sim		sim;
	pthread_t	monitor;

	if (ac < 2)
		return (1);
	if (!init_simulation(&sim, ft_atoi(av[1])))
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
