/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:30:21 by yannis            #+#    #+#             */
/*   Updated: 2025/07/29 13:16:58 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	if (philo->data->flag_fork[philo->id - 1] == 0)
	{
		philo->data->flag_fork[philo->id - 1] = philo->id;
		safe_print(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->nb_philo]);
	if (philo->data->flag_fork[philo->id % philo->data->nb_philo] == 0)
	{
		philo->data->flag_fork[philo->id % philo->data->nb_philo] = philo->id;
		safe_print(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->nb_philo]);
	if (check_for_meal(philo))
		return (1);
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	if (philo->data->flag_fork[philo->id - 1] == philo->id)
		philo->data->flag_fork[philo->id - 1] = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->nb_philo]);
	if (philo->data->flag_fork[philo->id % philo->data->nb_philo] == philo->id)
		philo->data->flag_fork[philo->id % philo->data->nb_philo] = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->nb_philo]);
	return (0);
}
