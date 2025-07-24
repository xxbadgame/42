/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:52:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/24 20:56:58 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	take_forks_even(t_philo *philo)
{
	lock_mutex(philo->right_fork, philo, 1);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
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
	lock_mutex(philo->right_fork, philo, 1);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	return (0);
}

int	even_philo(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		if (take_forks_even(philo) == -1)
			return (-1);
	}
	else if (philo->left_fork > philo->right_fork)
	{
		if (take_forks_odd(philo) == -1)
			return (-1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_settings->number_of_philo == 1)
	{
		safe_print("has taken a fork", philo->id, philo->mutex, philo);
		return (-1);
	}
	if (philo->id % 2 == 0 && philo->left_fork < philo->right_fork)
	{
		if (take_forks_even(philo) == -1)
			return (-1);
	}
	else if (philo->id % 2 != 0 && philo->left_fork > philo->right_fork)
	{
		if (take_forks_odd(philo) == -1)
			return (-1);
	}
	else if (philo->philo_settings->number_of_philo % 2 == 0)
	{
		if (even_philo(philo) == -1)
			return (-1);
	}
	return (0);
}
