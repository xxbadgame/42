/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:03:47 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 21:42:16 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return ((void)pthread_mutex_destroy(&data->print_mutex), 1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
	{
		pthread_mutex_destroy(&data->print_mutex);
		return ((void)pthread_mutex_destroy(&data->death_mutex), 1);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			destroy_mutex_i(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos) {
		return (1);
	}
	data->flag_forks = malloc(sizeof(int) * data->nb_philo);
	if (!data->flag_forks)
		return (free(data->philos), 1);
	i = -1;
	while (++i < data->nb_philo)
		data->flag_forks[i] = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free(data->philos), free(data->flag_forks), 1);
	if (init_mutex(data))
		return (free(data->philos), free(data->flag_forks), free(data->forks), 1);
	return (0);
}

void	set_philo_info(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].alive = 1;
	data->philos[i].last_meal_time = 0;
	data->philos[i].eat_count = 0;
	data->philos[i].data = data;
}

int	init_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->nb_philo)
	{
		set_philo_info(data, i);
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			destroy_mutex_and_free(data, i);
			return (1);
		}
		i++;
	}
	data->time_start = time_now_ms();
	pthread_mutex_unlock(&data->meal_mutex);
	return (0);
}
