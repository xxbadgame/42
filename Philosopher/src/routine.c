/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:21:22 by yannis            #+#    #+#             */
/*   Updated: 2025/03/20 12:22:20 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	r_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->r_fork);
	mutex_print("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	mutex_print("has taken a fork", philo);
	mutex_print("is eating", philo);
	philo->eat = 1;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->eatex);
	philo->last_time_eat = time_now_ms();
	philo->nb_meals++;
	pthread_mutex_unlock(philo->eatex);
	philo->eat = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
    return (0);
}

int	r_sleep(t_philosopher *philo)
{
	mutex_print("is sleeping", philo);
	usleep(philo->time_to_sleep * 1000);
    return (0);
}

int	r_think(t_philosopher *philo)
{
	mutex_print("is thinking", philo);
    return (0);
}