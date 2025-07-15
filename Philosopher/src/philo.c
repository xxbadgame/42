/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 08:57:36 by yannis            #+#    #+#             */
/*   Updated: 2025/07/15 15:53:27 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	secure_in_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print("has taken a fork", philo->id, philo->mutex,
			time_sim(philo->philo_settings));
		if (philo->philo_settings->number_of_philo == 1)
			return (-1);
		pthread_mutex_lock(philo->left_fork);
		safe_print("has taken a fork", philo->id, philo->mutex,
			time_sim(philo->philo_settings));
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print("has taken a fork", philo->id, philo->mutex,
			time_sim(philo->philo_settings));
		if (philo->philo_settings->number_of_philo == 1)
			return (-1);
		pthread_mutex_lock(philo->right_fork);
		safe_print("has taken a fork", philo->id, philo->mutex,
			time_sim(philo->philo_settings));
	}
	return (0);
}

int	meal_event(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	safe_print("is eating", philo->id, philo->mutex,
		time_sim(philo->philo_settings));
	usleep(philo->philo_settings->time_to_eat * 1000);
	philo->eat_count++;
	philo->last_meal_time = time_now_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
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
		safe_print("is thinking", philo->id, philo->mutex,
			time_sim(philo->philo_settings));
		if (secure_in_routine(philo) == -1)
			return (NULL);
		meal_event(philo);
		safe_print("is sleeping", philo->id, philo->mutex,
			time_sim(philo->philo_settings));
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
		if (philo_set->number_of_philo > 1)
		{
			philos[i].right_fork = &philo_set->forks[(i + 1)
				% philo_set->number_of_philo];
		}
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		philos[i].last_meal_time = time_now_ms();
		philos[i].eat_count = 0;
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			safe_print("Failed to create thread", philos[i].id, mutex,
				time_sim(philo_set));
			return (-1);
		}
		i++;
	}
	return (0);
}
