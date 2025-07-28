/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:19:56 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 17:20:03 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_philo_settings
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

typedef struct s_global_mutex
{
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
}						t_global_mutex;

typedef struct s_philo
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