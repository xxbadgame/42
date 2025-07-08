/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 08:57:36 by yannis            #+#    #+#             */
/*   Updated: 2025/07/08 13:23:25 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	secure_in_routine(t_philo *philo)
{
	safe_print("is thinking", philo->id, philo->mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print("has taken a fork", philo->id, philo->mutex);
		pthread_mutex_lock(philo->left_fork);
		safe_print("has taken a fork", philo->id, philo->mutex);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print("has taken a fork", philo->id, philo->mutex);
		pthread_mutex_lock(philo->right_fork);
		safe_print("has taken a fork", philo->id, philo->mutex);
	}
	return (0);
}

int	meal_event(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = time_now_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print("is eating", philo->id, philo->mutex);
	usleep(philo->philo_settings->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(philo->id * 500);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex->death_mutex);
		if (philo->philo_settings->is_dead)
		{
			pthread_mutex_unlock(&philo->mutex->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex->death_mutex);
		secure_in_routine(philo);
		meal_event(philo);
		safe_print("is sleeping", philo->id, philo->mutex);
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

int	init_philo(t_philo_settings *philo_set, t_global_mutex *mutex,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philo_set->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].mutex = mutex;
		philos[i].philo_settings = philo_set;
		philos[i].left_fork = &philo_set->forks[i];
		philos[i].right_fork = &philo_set->forks[(i + 1)
			% philo_set->number_of_philo];
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		philos[i].last_meal_time = time_now_ms();
		philos[i].eat_count = 0;
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			safe_print("Failed to create thread for philo", philos[i].id,
				mutex);
			return (-1);
		}
		i++;
	}
	return (0);
}
