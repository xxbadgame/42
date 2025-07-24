/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:59:22 by yannis            #+#    #+#             */
/*   Updated: 2025/07/24 20:47:29 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	check_dead_or_done(t_philo *philos, int i, t_philo_settings *philo_set,
		int *done)
{
	size_t	time_since_meal;

	pthread_mutex_lock(&philos[i].meal_mutex);
	time_since_meal = time_now_ms() - philos[i].last_meal_time;
	if (philo_set->nb_time_philo_must_eat > 0
		&& philos[i].eat_count > philo_set->nb_time_philo_must_eat)
		(*done)++;
	pthread_mutex_unlock(&philos[i].meal_mutex);
	if (time_since_meal > philo_set->time_to_die)
	{
		pthread_mutex_lock(&philos[i].mutex->death_mutex);
		if (!philo_set->is_dead)
		{
			philo_set->is_dead = 1;
			pthread_mutex_unlock(&philos[i].mutex->death_mutex);
			safe_print("died", philos[i].id, philos[i].mutex, &philos[i]);
		}
		else if (philo_set->is_dead)
			return (pthread_mutex_unlock(&philos[i].mutex->death_mutex), 1);
		return (1);
	}
	return (0);
}

int	is_done(t_philo_settings *philo_set, int done, t_philo *philos)
{
	if (philo_set->nb_time_philo_must_eat > 0
		&& done == philo_set->number_of_philo)
	{
		pthread_mutex_lock(&philos[0].mutex->death_mutex);
		philo_set->is_dead = 1;
		pthread_mutex_unlock(&philos[0].mutex->death_mutex);
		return (0);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo				*philos;
	t_philo_settings	*philo_set;
	int					i;
	int					done;

	philos = (t_philo *)arg;
	philo_set = philos[0].philo_settings;
	while (1)
	{
		i = 0;
		done = 0;
		while (i < philo_set->number_of_philo)
		{
			if (check_dead_or_done(philos, i, philo_set, &done) == 1)
				return (NULL);
			i++;
		}
		is_done(philo_set, done, philos);
		usleep(10);
	}
	return (NULL);
}
