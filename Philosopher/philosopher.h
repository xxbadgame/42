/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:33 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/16 15:24:31 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo_settings
{
	int					number_of_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					nb_time_philo_must_eat;
	pthread_mutex_t		*forks;
	int					is_dead;
	size_t				time_start;
}						t_philo_settings;

typedef struct global_mutex
{
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
}						t_global_mutex;

typedef struct philo
{
	t_philo_settings	*philo_settings;
	int					id;
	pthread_t			thread;
	t_global_mutex		*mutex;
	pthread_mutex_t		*left_fork;
	int					locked_left;
	pthread_mutex_t		*right_fork;
	int					locked_right;
	size_t				last_meal_time;
	pthread_mutex_t		meal_mutex;
	int					eat_count;
}						t_philo;

/*
 * global mutex
 */
int						safe_print(char *message, int number,
							t_global_mutex *mutex, t_philo *philo);

/*
 * init
 */
int						init_philo(t_philo_settings *philo_set,
							t_global_mutex *mutex, t_philo *philos, int i);
int						init_philo_threads(t_philo_settings *philo_set,
							t_global_mutex *mutex, t_philo *philos);
int						init_forks(t_philo_settings *philo_set);

/*
 * utils
 */
size_t					time_now_ms(void);
size_t					time_sim(t_philo_settings *philo_set);
void					destroy_all(t_philo_settings *philo_set,
							t_global_mutex *mutex, t_philo *philos);
int						is_dead(t_philo *philo);

/*
 * monitor
 */
void					*monitor_routine(void *arg);

/*
 * lock mutex
 */
void					lock_mutex(pthread_mutex_t *fork, t_philo *philo,
							int s);
void					unlock_mutex(pthread_mutex_t *fork, t_philo *philo,
							int s);

/*
 * lock mutex
 */
int						take_forks(t_philo *philo);
int						drop_forks(t_philo *philo);

#endif