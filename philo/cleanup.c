/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:46:22 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/13 19:52:58 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_forks(t_sim *sim, int n)
{
	while (n--)
		pthread_mutex_destroy(&sim->forks[n]);
	free(sim->forks);
	sim->forks = NULL;
}

void	cleanup(t_sim *sim, t_philo *philosophers, pthread_t *threads)
{
	int	i;

	if (sim && sim->forks)
	{
		i = 0;
		while (i < sim->nb_philos)
			pthread_mutex_destroy(&sim->forks[i++]);
		pthread_mutex_destroy(&sim->stop_mutex);
		pthread_mutex_destroy(&sim->print_mutex);
		free(sim->forks);
		sim->forks = NULL;
	}
	if (philosophers)
	{
		i = 0;
		while (i < sim->nb_philos)
			pthread_mutex_destroy(&philosophers[i++].meal_mutex);
		free(philosophers);
	}
	if (threads)
		free(threads);
}
