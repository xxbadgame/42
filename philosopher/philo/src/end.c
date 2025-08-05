/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:08 by yannis            #+#    #+#             */
/*   Updated: 2025/08/04 10:36:10 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eat(t_philo *philo)
{
	philo->nbr_meal++;
	pthread_mutex_lock(&philo->data->alive);
	if (philo->nbr_meal >= philo->data->nb_must_eat)
	{
		philo->data->philo_full++;
		philo->nbr_meal = -1;
	}
	if (philo->data->philo_full == philo->data->nb_philo)
		philo->data->status = 1;
	pthread_mutex_unlock(&philo->data->alive);
	return (0);
}

int	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->alive);
	if (philo->data->status)
	{
		pthread_mutex_unlock(&philo->data->alive);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->alive);
	return (0);
}

int	is_dead(t_philo *philo)
{
	size_t	time_to_print;

	if (check_status(philo))
		return (1);
	time_to_print = ft_time_from_start(philo->data->time_start);
	if (!check_status(philo) && ft_time_from_start(philo->data->time_start)
		- philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->alive);
		philo->data->status = 1;
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d died\n", time_to_print, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->alive);
		return (1);
	}
	if (check_status(philo))
		return (1);
	return (0);
}
