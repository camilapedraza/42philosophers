/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/16 19:54:36 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

#include "philosophers.h"

int	main(int ac, char **av)
{
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
	if (pthread_create(&monitor, NULL, monitor_routine, philosophers) != 0)
	{	
		cleanup(&sim, &philosophers, &threads);
		return (EXIT_FAILURE);
	}
	pthread_join(monitor, NULL);
	cleanup(&sim, &philosophers, &threads);
	return (EXIT_SUCCESS);
}
