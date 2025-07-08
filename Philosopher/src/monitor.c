/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:59:22 by yannis            #+#    #+#             */
/*   Updated: 2025/07/07 09:27:01 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*monitor_routine(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	t_philo_settings *philo_set = philos[0].philo_settings;
	size_t	time_since_meal;
	int		i;

	while (1)
	{
		i = 0;
		int done = 0;

		while (i < philo_set->number_of_philo)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			time_since_meal = time_now_ms() - philos[i].last_meal_time;

			if (philo_set->nb_time_philo_must_eat > 0
				&& philos[i].eat_count >= philo_set->nb_time_philo_must_eat)
				done++;

			pthread_mutex_unlock(&philos[i].meal_mutex);

			if (time_since_meal > philo_set->time_to_die)
			{
				pthread_mutex_lock(&philos[i].mutex->death_mutex);
				if (!philo_set->is_dead)
				{
					philo_set->is_dead = 1;
					safe_print("died", philos[i].id, philos[i].mutex);
				}
				pthread_mutex_unlock(&philos[i].mutex->death_mutex);
				return (NULL);
			}
			i++;
		}

		if (philo_set->nb_time_philo_must_eat > 0
			&& done == philo_set->number_of_philo)
		{
			pthread_mutex_lock(&philos[0].mutex->death_mutex);
			philo_set->is_dead = 1;
			pthread_mutex_unlock(&philos[0].mutex->death_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
