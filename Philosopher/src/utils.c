/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:10:49 by yannis            #+#    #+#             */
/*   Updated: 2025/03/18 10:39:21 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

size_t time_now_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void mutex_print(char *str, t_philosopher *philo)
{
    pthread_mutex_lock(philo->printex);
    printf("%ld %d %s\n", time_now_ms() , philo->index_philo + 1, str);
    pthread_mutex_unlock(philo->printex);
}