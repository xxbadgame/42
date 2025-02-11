/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/11 11:50:42 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

// param : nb_phil : 3, ttd : 800, tte : 200, tts : 200, (eat_by_phil)
pthread_mutex_t mutex;

void* routine(void *arg) {
    pthread_mutex_lock(&mutex);
    struct timeval start;
    int index = *(int *)arg;
    usleep(500000);
    gettimeofday(&start, NULL);
    printf("time : %ld, philospher : %d\n", start.tv_sec * 1000 + start.tv_usec / 1000, index);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int create_philosophers(t_dinner_table *dt, pthread_t *th)
{
    int i;

    i = 0;
    while (i <= dt->nb_p)
    {
        int *a = malloc(sizeof(int));
        *a = i + 1;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            return (perror("Failed to create thread"), -1);
        i++;
    }
    return (0);
}

int destroy_philosophers(t_dinner_table *dt, pthread_t *th)
{
    int i;

    i = 0;
    while (i < dt->nb_p)
    {
        if (pthread_join(th[i], NULL) != 0)
            return (perror("Failed to create thread"), -1);
        i++;
    }
    return (0);
}

int main(int arc, char **argv)
{
    t_dinner_table dt;
    pthread_t *th;
    
    dt.nb_p = 4;
    dt.ttd = 800;
    dt.tte = 200;
    dt.tts = 200;
    pthread_mutex_init(&mutex, NULL);
    th = malloc (dt.nb_p * sizeof(pthread_t));
    create_philosophers(&dt, th);
    destroy_philosophers(&dt, th);
    pthread_mutex_destroy(&mutex);
    free(th);
    return 0;
}
