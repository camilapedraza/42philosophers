/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:23 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/06 19:57:10 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_simulation
{
	int				stop;
	pthread_mutex_t	stop_mutex;
}	t_sim;

typedef struct s_philosopher
{
	int		id;

	t_sim	*sim;
}	t_philo;

/* UTILITIES */
int	ft_atoi(const char *nptr);

#endif