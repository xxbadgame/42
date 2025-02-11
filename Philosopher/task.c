/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:46:14 by yannis            #+#    #+#             */
/*   Updated: 2025/02/11 11:51:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

pthread_mutex_t mutex;

void* eat(void *arg) {
    pthread_mutex_lock(&mutex);
    struct timeval start;
    int index = *(int *)arg;
    usleep(500000);
    gettimeofday(&start, NULL);
    printf("time : %ld, philospher : %d\n", start.tv_sec * 1000 + start.tv_usec / 1000, index);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* think(void *arg) {
    pthread_mutex_lock(&mutex);
    struct timeval start;
    int index = *(int *)arg;
    usleep(500000);
    gettimeofday(&start, NULL);
    printf("time : %ld, philospher : %d\n", start.tv_sec * 1000 + start.tv_usec / 1000, index);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* sleep(void *arg) {
    pthread_mutex_lock(&mutex);
    struct timeval start;
    int index = *(int *)arg;
    usleep(500000);
    gettimeofday(&start, NULL);
    printf("time : %ld, philospher : %d\n", start.tv_sec * 1000 + start.tv_usec / 1000, index);
    pthread_mutex_unlock(&mutex);

    return NULL;
}