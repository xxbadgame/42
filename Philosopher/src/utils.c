/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:19:06 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/17 21:33:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	checker_lock(t_philo *philo)
{
	if (philo->locked_right == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->locked_right = 0;
	}
	if (philo->locked_left == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->locked_left = 0;
	}
}

void	lock_mutex(pthread_mutex_t *fork, t_philo *philo, int s)
{
	pthread_mutex_lock(fork);
	if (s == 0)
		philo->locked_left = 1;
	else if (s == 1)
		philo->locked_right = 1;
}

void	unlock_mutex(pthread_mutex_t *fork, t_philo *philo, int s)
{
	pthread_mutex_unlock(fork);
	if (s == 0)
		philo->locked_left = 0;
	else if (s == 1)
		philo->locked_right = 0;
}

int	wait_check_dead(t_philo *philo, size_t wait_time)
{
	size_t	time;

	time = time_now_ms();
	while (time_now_ms() - time < wait_time)
	{
		if (is_dead(philo) == 1)
			return (-1);
		usleep(10);
	}
	return (0);
}
