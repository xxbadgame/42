/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/10 22:06:31 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

// param : nb_phil : 3, ttd : 800, tte : 200, tts : 200, (eat_by_phil)

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    int i;

    i = 0;
    while (i < 2000)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int create_philosophers(t_dinner_table *dt, pthread_t *th)
{
    int i;

    i = 0;
    while (i < dt->nb_p)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
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
    printf("Number of mails: %d\n", mails);
    free(th);
    return 0;
}
