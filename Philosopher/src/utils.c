/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:10:49 by yannis            #+#    #+#             */
/*   Updated: 2025/03/17 16:47:39 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

size_t time_now_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int create_printex()
{
    int i;
    pthread_mutex_t printex;
    
    i = 0;
    if(pthread_mutex_init(&printex, NULL) != 0)
        return (perror("Failed to create fork"), -1);
    return (0);
}

void mutex_print(char *str, t_philosopher *philo)
{
    pthread_mutex_lock(philo->printex);
    printf("%ld %d %s\n", time_now_ms() , philo->index_philo + 1, str);
    pthread_mutex_unlock(philo->printex);
}