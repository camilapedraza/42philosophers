/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/06 19:56:29 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

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
	printf("Philosopher %d started\n", philosopher->id);
	while (!should_sim_stop(philosopher->sim))
	{
		printf("Philosopher %d is working\n", philosopher->id);
		usleep(200000);
	}
	printf("Philosopher %d stopped\n", philosopher->id);
	return (NULL);
}

// TODO guard clause for ac < 4
int	main(int ac, char **av)
{
	int			n;
	int			i;
	pthread_t	*threads;
	t_philo		*philosophers;
	t_sim		sim;

	if (ac < 1)
		return (1);
	n = ft_atoi(av[1]);
	if (n <= 0)
		return (1);
	threads = malloc(sizeof(pthread_t) * n);
	philosophers = malloc(sizeof(t_philo) * n);
	if (!threads || !philosophers)
		return (1);
	sim.stop = 0;
	pthread_mutex_init(&sim.stop_mutex, NULL);
	i = 0;
	while (i < n)
	{
		philosophers[i].id = i + 1;
		philosophers[i].sim = &sim;
		pthread_create(&threads[i], NULL, routine, &philosophers[i]);
		i++;
	}
	sleep(1);
	pthread_mutex_lock(&sim.stop_mutex);
	sim.stop = 1;
	pthread_mutex_unlock(&sim.stop_mutex);
	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);
	free(threads);
	free(philosophers);
	pthread_mutex_destroy(&sim.stop_mutex);
	return (0);
}
