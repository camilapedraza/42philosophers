/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:23 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/09 16:02:25 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* STATUS MESSAGES */

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DEATH	"died"

# define FAILURE 0
# define SUCCESS 1

typedef struct s_simulation
{
	long			start_time;
	int				stop;
	int				nb_philosophers;

	pthread_mutex_t *forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t print_mutex;
}	t_sim;

typedef struct s_philosopher
{
	int		id;

	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;

	t_sim	*sim;
}	t_philo;

/* PHILOSOPHER TASKS */
void	take_forks(t_philo *philosopher);
void	release_forks(t_philo *philosopher);

/* UTILITIES */
long	get_time_ms(void);
long	timestamp_ms(t_sim *sim);
void	print_status(t_philo *philosopher, const char *status);
int		ft_atoi(const char *nptr);

#endif