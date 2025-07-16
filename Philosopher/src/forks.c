/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:52:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/16 14:53:29 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	take_forks_even(t_philo *philo)
{
	lock_mutex(philo->right_fork, philo, 1);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	if (philo->philo_settings->number_of_philo == 1)
		return (-1);
	lock_mutex(philo->left_fork, philo, 0);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	return (0);
}

int	take_forks_odd(t_philo *philo)
{
	lock_mutex(philo->left_fork, philo, 0);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	if (philo->philo_settings->number_of_philo == 1)
		return (-1);
	lock_mutex(philo->right_fork, philo, 1);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_forks_even(philo) == -1)
			return (-1);
	}
	else
	{
		if (take_forks_odd(philo) == -1)
			return (-1);
	}
	return (0);
}

int	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		unlock_mutex(philo->right_fork, philo, 1);
		unlock_mutex(philo->left_fork, philo, 0);
	}
	else
	{
		unlock_mutex(philo->left_fork, philo, 0);
		unlock_mutex(philo->right_fork, philo, 1);
	}
	return (0);
}
