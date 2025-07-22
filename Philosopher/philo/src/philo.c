/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 08:57:36 by yannis            #+#    #+#             */
/*   Updated: 2025/07/18 09:50:53 by yannis           ###   ########.fr       */
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
	if (safe_print("is eating", philo->id, philo->mutex, philo) == -1)
		return (-1);
	if (wait_check_dead(philo, philo->philo_settings->time_to_eat) == -1)
		return (-1);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eat_count++;
	philo->last_meal_time = time_now_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_dead(philo) == 0)
	{
		if (take_forks(philo) == -1)
			return (checker_lock(philo), NULL);
		if (meal_event(philo) == -1)
			return (checker_lock(philo), NULL);
		checker_lock(philo);
		if (safe_print("is sleeping", philo->id, philo->mutex, philo) == -1)
			return (checker_lock(philo), NULL);
		if (wait_check_dead(philo, philo->philo_settings->time_to_sleep) == -1)
			return (NULL);
		if (safe_print("is thinking", philo->id, philo->mutex, philo) == -1)
			return (checker_lock(philo), NULL);
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
