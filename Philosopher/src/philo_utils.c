/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 09:26:09 by yannis            #+#    #+#             */
/*   Updated: 2025/07/09 07:46:38 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

size_t	time_now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	safe_print(char *message, int number, t_global_mutex *mutex)
{
	pthread_mutex_lock(&mutex->print_mutex);
	printf("%ld %d %s\n", time_now_ms(), number, message);
	pthread_mutex_unlock(&mutex->print_mutex);
	return (0);
}

void	destroy_all(t_philo_settings *philo_set, t_global_mutex *mutex, t_philo *philos)
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

