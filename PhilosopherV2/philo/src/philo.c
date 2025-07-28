/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:28:27 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 22:03:43 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->data->meal_mutex);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
        is_thinking(philo);
		// if (is_dead(philo))
		// 	break ;
		is_eating(philo);
		// if (is_dead(philo))
		// 	break ;
		is_sleeping(philo);
	}
	return (NULL);
}