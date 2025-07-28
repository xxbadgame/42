/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:58:57 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 22:04:05 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philo *philo)
{
	// if (is_dead(philo))
	// 	return (1);
	safe_print(philo, "is thinking");
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	long long	time;

	// if (check_status(philo))
	// 	return (1);
	safe_print(philo, "is sleeping");
	drop_forks(philo);
    
	// time = ft_time_from_start(philo->data->time_start);
	// while (!is_dead(philo) \
	// && (ft_time_from_start(philo->data->time_start) - time) \
	// < philo->data->time_to_sleep)
	// 	usleep(10 * philo->data->nb_philo);
	return (0);
}

int	is_eating(t_philo *philo)
{
	while (!check_status(philo) && !pick_forks(philo))
		usleep(10 * philo->data->nb_philo);
	return (0);
}