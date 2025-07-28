/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:52:11 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/28 18:02:17 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	pthread_mutex_lock(philo->left_fork);
	if (safe_print("has taken a fork", philo->id, philo->mutex, philo) == -1)
		return (-1);
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}
