/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:46:22 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/18 16:16:27 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_threads(pthread_t **threads, int i)
{
	while (--i >= 0)
		pthread_join((*threads)[i], NULL);
	free(*threads);
	*threads = NULL;
}

void	cleanup_philosophers(t_philo **philosophers, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&(*philosophers)[i].meal_mutex);
	free(*philosophers);
	*philosophers = NULL;
}

void	cleanup_forks(t_sim *sim, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&sim->forks[i]);
	free(sim->forks);
	sim->forks = NULL;
}

void	cleanup_sim(t_sim *sim, int i)
{
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	if (sim->forks)
		cleanup_forks(sim, i);
}

void	cleanup(t_sim *sim, t_philo **philosophers, pthread_t **threads)
{
	if (threads && *threads)
		cleanup_threads(threads, sim->nb_philos);
	if (philosophers && *philosophers)
		cleanup_philosophers(philosophers, sim->nb_philos);
	if (sim)
		cleanup_sim(sim, sim->nb_philos);
}
