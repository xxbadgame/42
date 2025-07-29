/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:31:33 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 22:46:42 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	time_now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	safe_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        return ;
    }
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", (time_now_ms() - philo->data->time_start),
		philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
    pthread_mutex_unlock(&philo->data->death_mutex);
}

int	wait_check_dead(t_philo *philo, size_t wait_time)
{
	size_t	time;
    (void)philo;

	time = time_now_ms();
	while (time_now_ms() - time < wait_time)
	{
		// if (is_dead(philo) == 1)
		// 	return (1);
		usleep(10);
	}
	return (0);
}