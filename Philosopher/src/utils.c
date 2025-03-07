/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:10:49 by yannis            #+#    #+#             */
/*   Updated: 2025/03/07 06:41:31 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

size_t time_now_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void mutex_print(char *str, pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    printf("%s", str);
    pthread_mutex_unlock(mutex);
}