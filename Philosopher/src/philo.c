/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 08:57:36 by yannis            #+#    #+#             */
/*   Updated: 2025/07/16 15:19:30 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->death_mutex);
	if (philo->philo_settings->is_dead)
	{
		pthread_mutex_unlock(&philo->mutex->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex->death_mutex);
	return (0);
}

int	meal_event(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (safe_print("is eating", philo->id, philo->mutex, philo) == -1)
		return (-1);
	usleep(philo->philo_settings->time_to_eat * 1000);
	philo->eat_count++;
	philo->last_meal_time = time_now_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(philo->id * 500);
	while (is_dead(philo) == 0)
	{
		if (safe_print("is thinking", philo->id, philo->mutex, philo) == -1)
			return (NULL);
		if (take_forks(philo) == -1)
			return (NULL);
		if (meal_event(philo) == -1)
			return (NULL);
		drop_forks(philo);
		if (safe_print("is sleeping", philo->id, philo->mutex, philo) == -1)
			return (NULL);
		usleep(philo->philo_settings->time_to_sleep * 1000);
	}
	return (NULL);
}

int	init_forks(t_philo_settings *philo_set)
{
	int	i;

	i = 0;
	while (i < philo_set->number_of_philo)
	{
		pthread_mutex_init(&philo_set->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philo_threads(t_philo_settings *philo_set, t_global_mutex *mutex,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philo_set->number_of_philo)
	{
		init_philo(philo_set, mutex, philos, i);
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			safe_print("Failed to create thread", philos[i].id, mutex,
				&philos[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}
