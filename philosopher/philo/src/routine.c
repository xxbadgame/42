/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:34:50 by yannis            #+#    #+#             */
/*   Updated: 2025/07/29 13:47:20 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	safe_print(philo, "is thinking");
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	safe_print(philo, "is sleeping");
	drop_forks(philo);
	wait_check_dead(philo, philo->data->time_to_sleep);
	return (0);
}

int	is_eating(t_philo *philo)
{
	while (!check_status(philo) && !take_forks(philo))
		usleep(10 * philo->data->nb_philo);
	return (0);
}

int	no_race_conditions(t_philo *philo)
{
	int	left;
	int	right;
	int	has_left;
	int	has_right;

	left = philo->id - 1;
	right = philo->id % philo->data->nb_philo;
	has_left = 0;
	has_right = 0;
	pthread_mutex_lock(&philo->data->forks[left]);
	has_left = (philo->data->flag_fork[left] == philo->id);
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_lock(&philo->data->forks[right]);
	has_right = (philo->data->flag_fork[right] == philo->id);
	pthread_mutex_unlock(&philo->data->forks[right]);
	return (has_left && has_right);
}

int	check_for_meal(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	if (no_race_conditions(philo) && philo->id - 1 != philo->id
		% philo->data->nb_philo)
	{
		safe_print(philo, "is eating");
		philo->last_meal = ft_time_from_start(philo->data->time_start);
		wait_check_dead(philo, philo->data->time_to_eat);
		if (philo->data->nb_must_eat != -1)
			all_eat(philo);
		return (1);
	}
	return (0);
}
