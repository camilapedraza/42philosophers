/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:24:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/18 17:59:14 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_help(void)
{
	printf("./philo requires at least 4 arguments (positive integers):\n");
	printf("- <p> number of Philosophers at the table\n");
	printf(
		"- <d> milliseconds between meals (otherwise Death occurs)\n"
		);
	printf("- <m> milliseconds Meals should last\n");
	printf("- <s> milliseconds Sleep should last\n");
	printf("- <n> optional: number of meals needed so simulation can stop\n");
	printf("(if no <n>, simulation stops only when a philosopher dies)\n");
	printf("\n./philo <p> <d> <m> <s> <n>\n");
}

static char	*status_msg(t_status status)
{
	if (status == THINKING)
		return ("is thinking");
	if (status == SLEEPING)
		return ("is sleeping");
	if (status == EATING)
		return ("is eating");
	if (status == TAKEN_FORK)
		return ("has taken a fork");
	if (status == DEAD)
		return ("died");
	return ("");
}

void	print_status(t_philo *philosopher, t_status status)
{
	long	timestamp;

	pthread_mutex_lock(&philosopher->sim->print_mutex);
	pthread_mutex_lock(&philosopher->sim->stop_mutex);
	if (philosopher->sim->stop && status != DEAD)
	{
		pthread_mutex_unlock(&philosopher->sim->stop_mutex);
		pthread_mutex_unlock(&philosopher->sim->print_mutex);
		return ;
	}
	timestamp = timestamp_ms(philosopher->sim);
	printf("%ld %d %s\n", timestamp, philosopher->id, status_msg(status));
	pthread_mutex_unlock(&philosopher->sim->stop_mutex);
	pthread_mutex_unlock(&philosopher->sim->print_mutex);
}
