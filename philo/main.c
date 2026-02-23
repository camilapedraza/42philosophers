/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/23 18:43:04 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_philo		*philosophers;
	t_sim		sim;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
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
