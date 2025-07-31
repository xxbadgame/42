/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:43 by yannis            #+#    #+#             */
/*   Updated: 2025/07/29 13:46:59 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, char *msg)
{
	size_t	time_to_print;

	pthread_mutex_lock(&philo->data->alive);
	if (philo->data->status)
	{
		pthread_mutex_unlock(&philo->data->alive);
		return ;
	}
	time_to_print = ft_time_from_start(philo->data->time_start);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", time_to_print, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->alive);
}

size_t	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	ft_time_from_start(size_t begin)
{
	if (!begin)
		begin = ft_get_time_ms();
	return (ft_get_time_ms() - begin);
}

void	wait_check_dead(t_philo *philo, size_t time)
{
	size_t	start_time;

	start_time = ft_time_from_start(philo->data->time_start);
	while (!is_dead(philo) && (ft_time_from_start(philo->data->time_start)
			- start_time) < time)
		usleep(10 * philo->data->nb_philo);
}
