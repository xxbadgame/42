/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:33 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/19 17:46:41 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

// philo character
typedef struct s_philosopher
{
	pthread_t		thread;
	int				index_philo;

	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;

	size_t			last_time_eat;
	int				*dead;
	int				*everyone_eat;
	int				nb_meals;
	int				eat;

	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

	pthread_mutex_t	*printex;
	pthread_mutex_t	*eatex;
    pthread_mutex_t *deadex;

}					t_philosopher;

// global data
typedef struct s_dinner_table
{
	int				nb_philo;
	int				time_now;
	int				dead_program;
	int				full_eat_program;

	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_each_philosopher_must_eat;

	t_philosopher	*all_philo;
	pthread_mutex_t	*all_forks;
	pthread_t		th_monitor;

	pthread_mutex_t	printex;
	pthread_mutex_t	eatex;
    pthread_mutex_t	deadex;

}					t_dinner_table;

// forks
int					create_forks(t_dinner_table *dt);
int					destroy_forks(t_dinner_table *dt);

// philosophers
void				*philo_routine(void *arg);
int					create_philosophers(t_dinner_table *dt);
int					destroy_philosophers(t_dinner_table *dt);

// routine
int					r_eat(t_philosopher *philo);
int					r_sleep(t_philosopher *philo);
int					r_think(t_philosopher *philo);

// monitor
void				*monitor_routine(void *arg);
int					create_monitor(t_dinner_table *dt);
int					destroy_monitor(t_dinner_table *dt);
int					actual_philo_dead(t_philosopher *philo);
int					check_all_philo_alive(t_dinner_table *dt);
int					everyone_full_eat(t_dinner_table *dt);

// utils
size_t				time_now_ms(void);
void				mutex_print(char *str, t_philosopher *philo);

#endif