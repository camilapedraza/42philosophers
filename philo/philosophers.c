/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/09 16:28:54 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

//TODO remove EXIT functions everywhere

#include "philosophers.h"

int	should_sim_stop(t_sim *sim)
{
	int	value;

	pthread_mutex_lock(&sim->stop_mutex);
	value = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (value);
}

void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	print_status(philosopher, "started");
	while (!should_sim_stop(philosopher->sim))
	{
		take_forks(philosopher);
		print_status(philosopher, EAT);
		usleep(200000);
		release_forks(philosopher);
		usleep(200000);
	}
	print_status(philosopher, "stopped");
	return (NULL);
}

int	init_threads(t_sim *sim, t_philo *philosophers, pthread_t **threads)
{
	int i;

	*threads = malloc(sizeof(pthread_t) * sim->nb_philosophers);
	if (!*threads)
		return (FAILURE);
	i = 0;
	while (i < sim->nb_philosophers)
	{
		pthread_create(&(*threads)[i], NULL, routine, &philosophers[i]);
		i++;
	}
	return (SUCCESS);
}
int	init_philosophers(t_sim *sim, t_philo **philosophers)
{
	int i;

	*philosophers = malloc(sizeof(t_philo) * sim->nb_philosophers);
	if (!*philosophers)
		return (FAILURE);
	i = 0;
	while (i < sim->nb_philosophers)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].sim = sim;
		(*philosophers)[i].fork_left = &sim->forks[i];
		(*philosophers)[i].fork_right = &sim->forks[(i + 1) % sim->nb_philosophers];
		i++;
	}
	return (SUCCESS);
}

int	init_simulation(t_sim *sim, int n)
{
	int i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!sim->forks)
		return (FAILURE);
	sim->start_time = get_time_ms();
	sim->nb_philosophers = n;
	sim->stop = 0;
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
	int			n;
	int			i;
	pthread_t	*threads;
	t_philo		*philosophers;
	t_sim		sim;

	if (ac < 2)
		return (1);
	n = ft_atoi(av[1]);
	if (n <= 0)
		return (1);
	if (!init_simulation(&sim, n))
		exit(EXIT_FAILURE);
	if (!init_philosophers(&sim, &philosophers))
		exit(EXIT_FAILURE);
	if (!init_threads(&sim, philosophers, &threads))
		exit(EXIT_FAILURE);
	sleep(1);
	pthread_mutex_lock(&sim.stop_mutex);
	sim.stop = 1;
	pthread_mutex_unlock(&sim.stop_mutex);
	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&sim.forks[i++]);
	pthread_mutex_destroy(&sim.stop_mutex);
	pthread_mutex_destroy(&sim.print_mutex);
	free(sim.forks);
	free(philosophers);
	free(threads);
	return (0);
}
