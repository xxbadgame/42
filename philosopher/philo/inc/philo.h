/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:50 by yannis            #+#    #+#             */
/*   Updated: 2025/07/31 20:56:12 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct					s_data
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					*flag_fork;
	pthread_mutex_t		alive;
	int					status;
	pthread_mutex_t		launch;
	pthread_mutex_t		print;
	int					nb_philo;
	int					philo_full;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					nb_must_eat;
	size_t				time_start;
};

struct					s_philo
{
	int					id;
	pthread_t			thread;
	int					nbr_meal;
	size_t				last_meal;
	t_data				*data;
};

int						is_eating(t_philo *philo);
int						no_race_conditions(t_philo *philo);
int						check_for_meal(t_philo *philo);
int						take_forks(t_philo *philo);
int						all_eat(t_philo *philo);
int						check_status(t_philo *philo);
int						is_dead(t_philo *philo);
void					destroy_philos(t_data *data, int i);
int						init_struct(t_data *data, int argc, char **argv);
void					destroy_mutex_and_free(t_data *data, int i);
int						init_mutex(t_data *data);
int						init_philo(t_data *data);
int						drop_forks(t_philo *philo);
int						is_sleeping(t_philo *philo);
void					*philo_routine(t_philo *philo);
void					set_philo_info(t_data *data, int i);
int						start_philos(t_data *data);
int						is_thinking(t_philo *philo);
void					safe_print(t_philo *philo, char *msg);
size_t					ft_get_time_ms(void);
size_t					ft_time_from_start(size_t begin);
void					wait_check_dead(t_philo *philo, size_t time);
int						check_error_args(int argc, char **argv);

#endif
