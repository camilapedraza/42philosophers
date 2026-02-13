/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:37:33 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/13 19:52:54 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
