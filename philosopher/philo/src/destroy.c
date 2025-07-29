/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:40:19 by yannis            #+#    #+#             */
/*   Updated: 2025/07/29 13:47:06 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	destroy_mutex_and_free(t_data *data, int i)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->launch);
	pthread_mutex_destroy(&data->alive);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->m_fork[i]);
		i--;
	}
	free(data->philos);
	free(data->fork);
	free(data->m_fork);
}
