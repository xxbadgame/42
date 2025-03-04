/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:46 by yannis            #+#    #+#             */
/*   Updated: 2025/03/04 11:22:28 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void* philo_routine(void *arg) 
{
    struct timeval start;
    t_philosopher *philo = (t_philosopher *)arg;
    t_dinner_table *dt = philo->dt;
    
    while (1)
    {
        pthread_mutex_lock(&dt->forks[philo->index_phil]);
        pthread_mutex_lock(&dt->forks[(philo->index_phil + 1) % dt->nb_philo]);
        
        gettimeofday(&start, NULL);
        printf("%ld %d is eating\n",start.tv_sec * 1000 + start.tv_usec / 1000 , philo->index_phil + 1);
        usleep(dt->time_to_eat * 1000);

        pthread_mutex_unlock(&dt->forks[philo->index_phil]);
        pthread_mutex_unlock(&dt->forks[(philo->index_phil + 1) % dt->nb_philo]);

        gettimeofday(&start, NULL);
        printf("%ld %d is sleeping\n",start.tv_sec * 1000 + start.tv_usec / 1000,  philo->index_phil + 1);
        usleep(dt->time_to_sleep * 1000);

        gettimeofday(&start, NULL);
        printf("%ld %d is thinking\n",start.tv_sec * 1000 + start.tv_usec / 1000,  philo->index_phil + 1);
    }

    return NULL;
}

int create_philosophers(t_dinner_table *dt)
{
    int i;

    dt->th_philo = malloc(dt->nb_philo * sizeof(pthread_t));
    if (!dt->th_philo)
        return (-1);

    i = 0;
    while (i < dt->nb_philo)
    {
        t_philosopher *philo = malloc(sizeof(t_philosopher)); 
        if(!philo)
            return (-1);
        philo->dt = dt;
        philo->index_phil = i;
        if (pthread_create(&dt->th_philo[i], NULL, &philo_routine, (void *)philo) != 0)
            return (perror("Failed to create philosophe"), -1);
        i++;
    }
    return (0);
}

int destroy_philosophers(t_dinner_table *dt)
{
    int i;

    i = 0;
    while (i < dt->nb_philo)
    {
        if (pthread_join(dt->th_philo[i], NULL) != 0)
            return (perror("Failed to destroy philosophe"), -1);
        i++;
    }
    free(dt->th_philo);
    return (0);
}