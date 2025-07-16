/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 09:26:09 by yannis            #+#    #+#             */
/*   Updated: 2025/07/16 14:45:09 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

size_t	time_now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	time_sim(t_philo_settings *philo_set)
{
	size_t	time_sim;

	time_sim = time_now_ms() - philo_set->time_start;
	return (time_sim);
}

int	safe_print(char *message, int number, t_global_mutex *mutex, t_philo *philo)
{
	size_t time;
	
	time = time_sim(philo->philo_settings);
	if (philo->philo_settings->is_dead)
		return (-1);
	pthread_mutex_lock(&mutex->print_mutex);
	printf("%ld %d %s\n", time, number, message);
	pthread_mutex_unlock(&mutex->print_mutex);
	return (0);
}

void	destroy_all(t_philo_settings *philo_set, t_global_mutex *mutex,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philo_set->number_of_philo)
	{
		pthread_mutex_destroy(&philo_set->forks[i]);
		i++;
	}
	i = 0;
	while (i < philo_set->number_of_philo)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philo_set->forks);
	free(philos);
	pthread_mutex_destroy(&mutex->print_mutex);
	pthread_mutex_destroy(&mutex->death_mutex);
}

int	init_philo(t_philo_settings *philo_set, t_global_mutex *mutex,
		t_philo *philos, int i)
{
	philos[i].id = i + 1;
	philos[i].mutex = mutex;
	philos[i].philo_settings = philo_set;
	philos[i].left_fork = &philo_set->forks[i];
	philos[i].locked_left = 0;
	philos[i].locked_right = 0;
	if (philo_set->number_of_philo > 1)
	{
		philos[i].right_fork = &philo_set->forks[(i + 1)
			% philo_set->number_of_philo];
	}
	philos[i].last_meal_time = time_now_ms();
	philos[i].eat_count = 0;
	return (0);
}
