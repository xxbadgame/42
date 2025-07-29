/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:23 by yannis            #+#    #+#             */
/*   Updated: 2025/07/29 14:06:43 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->launch, NULL))
		return ((void)pthread_mutex_destroy(&data->print), 1);
	if (pthread_mutex_init(&data->alive, NULL))
	{
		pthread_mutex_destroy(&data->print);
		return ((void)pthread_mutex_destroy(&data->alive), 1);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->m_fork[i], NULL))
		{
			destroy_mutex_and_free(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_struct(t_data *data, int argc, char **argv)
{
	data->status = 0;
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo > 200)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->philo_full = 0;
	data->nb_must_eat = -1;
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	data->fork = malloc(sizeof(int) * data->nb_philo);
	if (!data->fork)
		return (free(data->philos), 1);
	while (i < data->nb_philo)
		data->fork[i++] = 0;
	data->m_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->m_fork)
		return (free(data->philos), free(data->fork), 1);
	if (init_mutex(data))
		return (free(data->philos), free(data->fork), free(data->m_fork), 1);
	return (0);
}
