/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:23 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/10 21:02:05 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* STATUS MESSAGES */

# define FAILURE 0
# define SUCCESS 1

typedef enum e_status
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_status;

typedef struct s_simulation
{
	long			start_time;
	long			time_to_eat;
	long			time_to_die;
	bool			stop;
	int				nb_philos;

	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}	t_sim;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;

	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	meal_mutex;

	t_sim			*sim;
}	t_philo;

/* SIMULATION MONITOR */
void	*monitor_routine(void *arg);
bool	should_sim_stop(t_sim *sim);

/* PHILOSOPHER ROUTINE */
void	*philo_routine(void *arg);
void	take_forks(t_philo *philosopher);
void	release_forks(t_philo *philosopher);
void	eat(t_philo *philosopher);

/*	PRINT MODULE */
void	print_status(t_philo *philosopher, t_status status);

/* UTILITIES */
long	to_usec(long time);
long	get_time_ms(void);
long	timestamp_ms(t_sim *sim);
int		ft_atoi(const char *nptr);

#endif