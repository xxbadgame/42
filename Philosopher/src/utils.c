/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:19:06 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/16 16:01:16 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

checker_lock(t_philo *philo)
{
	if (philo->locked_right == 1)
		pthread_mutex_unlock(philo->right_fork);
	else if (philo->locked_left == 1)
		pthread_mutex_unlock(philo->left_fork);
}

void	lock_mutex(pthread_mutex_t *fork, t_philo *philo, int s)
{
	pthread_mutex_lock(fork);
	if (s == 0)
		philo->locked_left = 1;
	else if (s == 1)
		philo->locked_right = 1;
	if (is_dead(philo) == 1)
	{
		checker_lock(philo);
	}
}

void	unlock_mutex(pthread_mutex_t *fork, t_philo *philo, int s)
{
	pthread_mutex_unlock(fork);
	if (s == 0)
		philo->locked_left = 0;
	else if (s == 1)
		philo->locked_right = 0;
}
