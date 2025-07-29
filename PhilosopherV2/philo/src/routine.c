/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:58:57 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 23:23:11 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int take_forks(t_philo *philo)
{
	int left = philo->id - 1;
	int right = philo->id % philo->data->nb_philo;

	pthread_mutex_lock(&philo->data->forks[left]);
	if (philo->data->flag_forks[left] != 0)
	{
		pthread_mutex_unlock(&philo->data->forks[left]);
		return (1);
	}

	pthread_mutex_lock(&philo->data->forks[right]);
	if (philo->data->flag_forks[right] != 0)
	{
		pthread_mutex_unlock(&philo->data->forks[right]);
		pthread_mutex_unlock(&philo->data->forks[left]);
		return (1);
	}

	philo->data->flag_forks[left] = philo->id;
	philo->data->flag_forks[right] = philo->id;
	safe_print(philo, "has taken a fork");
	safe_print(philo, "has taken a fork");

	pthread_mutex_unlock(&philo->data->forks[right]);
	pthread_mutex_unlock(&philo->data->forks[left]);
	return (0);
}

int	drop_forks(t_philo *philo)
{
    int left = philo->id - 1;
    int right = philo->id % philo->data->nb_philo;
	pthread_mutex_lock(&philo->data->forks[left]);
	if (philo->data->flag_forks[left] == philo->id)
		philo->data->flag_forks[left] = 0;
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_lock(&philo->data->forks[right]);
	if (philo->data->flag_forks[right] == philo->id)
		philo->data->flag_forks[right] = 0;
	pthread_mutex_unlock(&philo->data->forks[right]);
	return (0);
}

int	is_thinking(t_philo *philo)
{
	// if (is_dead(philo))
	// 	return (1);
	safe_print(philo, "is thinking");
	return (0);
}

int	is_eating(t_philo *philo)
{
    while (take_forks(philo) != 0)
    {
        // if (check_status(philo)) // ou is_dead
        //     return (1);
        usleep(10 * philo->data->nb_philo);
    }
    safe_print(philo, "is eating");
    wait_check_dead(philo, philo->data->time_to_eat);
	// while (!check_status(philo) && !pick_forks(philo))
	// 	usleep(10 * philo->data->nb_philo);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	//long long	time;

	// if (check_status(philo))
	// 	return (1);
	safe_print(philo, "is sleeping");
	drop_forks(philo);
    wait_check_dead(philo, philo->data->time_to_sleep);
	return (0);
}