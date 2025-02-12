/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/12 12:45:16 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void* routine(void *arg) {
    struct timeval start;
    t_philosopher *philo = (t_philosopher *)arg;
    t_dinner_table *dt = philo->dt;
    
    pthread_mutex_lock(&dt->forks[philo->index_phil]);
    pthread_mutex_lock(&dt->forks[(philo->index_phil + 1) % dt->nb_phil]);
    
    gettimeofday(&start, NULL);
    printf("[%ld] Philosophe %d is eating\n",start.tv_sec * 1000 + start.tv_usec / 1000 , philo->index_phil + 1);
    usleep(1000000);

    pthread_mutex_unlock(&dt->forks[philo->index_phil]);
    pthread_mutex_unlock(&dt->forks[(philo->index_phil + 1) % dt->nb_phil]);

    printf("[%ld] Philosophe %d is thinking\n",start.tv_sec * 1000 + start.tv_usec / 1000,  philo->index_phil + 1);
    usleep(1000000);

    return NULL;
}

int create_philosophers(t_dinner_table *dt, pthread_t *th)
{
    int i;

    i = 0;
    while (i < dt->nb_phil)
    {
        t_philosopher *philo = malloc(sizeof(t_philosopher)); 
        if(!philo)
            return (-1);
        philo->dt = dt;
        philo->index_phil = i;
        if (pthread_create(&th[i], NULL, &routine, (void *)philo) != 0)
            return (perror("Failed to create thread"), -1);
        i++;
    }
    return (0);
}

int destroy_philosophers(t_dinner_table *dt, pthread_t *th)
{
    int i;

    i = 0;
    while (i < dt->nb_phil)
    {
        if (pthread_join(th[i], NULL) != 0)
            return (perror("Failed to create thread"), -1);
        i++;
    }
    return (0);
}

int main()
{
    t_dinner_table dt;
    pthread_t *threads;
    
    dt.nb_phil = 4;
    dt.time_to_die = 800;
    dt.time_to_eat = 200;
    dt.time_to_sleep = 200;

    init_forks(&dt);
    threads = malloc (dt.nb_phil * sizeof(pthread_t));
    if (!threads)
        return (-1);
        
    create_philosophers(&dt, threads);
    destroy_philosophers(&dt, threads);
    
    destroy_forks(&dt);

    free(threads);
    return 0;
}
