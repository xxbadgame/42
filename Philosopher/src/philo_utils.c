/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 09:26:09 by yannis            #+#    #+#             */
/*   Updated: 2025/07/15 15:53:34 by ynzue-es         ###   ########.fr       */
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

int	safe_print(char *message, int number, t_global_mutex *mutex, size_t time)
{
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
