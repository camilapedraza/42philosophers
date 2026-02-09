/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:15:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/09 15:49:29 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000L + time_now.tv_usec / 1000L);
}

long	timestamp_ms(t_sim *sim)
{
    return (get_time_ms() - sim->start_time);
}

void	print_status(t_philo *philosopher, const char *status)
{
	long	timestamp;
	
	pthread_mutex_lock(&philosopher->sim->print_mutex);
	timestamp = timestamp_ms(philosopher->sim);
	printf("%ld %d %s.\n", timestamp, philosopher->id, status);
	pthread_mutex_unlock(&philosopher->sim->print_mutex);
}

int	ft_atoi(const char *nptr)
{
	int	val;
	int	n;

	val = 1;
	n = 0;
	while ((*nptr == ' ') || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			val = val * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * val);
}
