/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:44:23 by mpedraza          #+#    #+#             */
/*   Updated: 2026/02/13 19:48:12 by mpedraza         ###   ########.fr       */
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

/* RETURN STATUS */

# define FAILURE 0
# define SUCCESS 1

/* PHILOSOPHER STATUS */

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
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				required_meals;

	long			start_time;

	bool			stop;

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

/* INITIALIZERS */
int		init_simulation(t_sim *sim, int ac, char **av);

/* ARGUMENT PARSER MODULE */
int		parse_args(t_sim *sim, int ac, char **av);

/* PHILOSOPHER ROUTINE */
void	*philo_routine(void *arg);

/* MONITOR ROUTINE */
void	*monitor_routine(void *arg);

/* PRINT MODULE */
void	print_help(void);
void	print_status(t_philo *philosopher, t_status status);

/* CLEANUP */
void	cleanup(t_sim *sim, t_philo *philosophers, pthread_t *threads);
void	cleanup_forks(t_sim *sim, int n);

/* UTILITIES */
long	to_usec(long time);
long	get_time_ms(void);
long	timestamp_ms(t_sim *sim);
int		ft_atoi(const char *nptr);

#endif