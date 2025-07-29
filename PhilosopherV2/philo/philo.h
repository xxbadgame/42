/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:47:55 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 22:45:50 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data t_data;
typedef struct s_philo t_philo;

struct s_data
{
	int				nb_philo;
	t_philo			*philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_time_philo_must_eat;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int				is_dead;
	pthread_mutex_t	*forks;
	int				*flag_forks;
	size_t			time_start;

};

struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			last_meal_time;
	int				eat_count;
	t_data			*data;
};

int					init_philo(t_data *data);
int					init_philo_threads(t_data *data);

void				*philo_routine(void *arg);

void				destroy_philo(t_data *data);
void				destroy_mutex_and_free(t_data *data, int i);

size_t				time_now_ms(void);
void				safe_print(t_philo *philo, char *message);
int					wait_check_dead(t_philo *philo, size_t wait_time);

int	is_thinking(t_philo *philo);
int	is_sleeping(t_philo *philo);
int	is_eating(t_philo *philo);