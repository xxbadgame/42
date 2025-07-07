/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 09:26:09 by yannis            #+#    #+#             */
/*   Updated: 2025/07/07 08:08:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

size_t	time_now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int safe_print(char *message, int number ,t_global_mutex *mutex)
{   
    pthread_mutex_lock(&mutex->print_mutex);
    printf("%ld %d %s\n", time_now_ms(), number, message);
    pthread_mutex_unlock(&mutex->print_mutex);
    return (0);
}