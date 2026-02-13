/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:03:10 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/13 18:04:32 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_valid_sim(t_sim *sim, int ac)
{
	if (sim->nb_philos < 1
		|| sim->time_to_die < 1
		|| sim->time_to_eat < 1
		|| sim->time_to_sleep < 1)
		return (FAILURE);
	if (ac == 6 && sim->required_meals < 1)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_args(t_sim *sim, int ac, char **av)
{
	int	n;

	n = ft_atoi(av[1]);
	sim->nb_philos = n;
	n = ft_atoi(av[2]);
	sim->time_to_die = n;
	n = ft_atoi(av[3]);
	sim->time_to_eat = n;
	n = ft_atoi(av[4]);
	sim->time_to_sleep = n;
	if (ac == 6)
	{
		n = ft_atoi(av[5]);
		sim->required_meals = n;
	}
	else
	sim->required_meals = 0;
	if (!is_valid_sim(sim, ac))
		return (FAILURE);
	return (SUCCESS);
}
