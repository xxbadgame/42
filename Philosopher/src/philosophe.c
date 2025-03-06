/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:46 by yannis            #+#    #+#             */
/*   Updated: 2025/03/06 12:23:47 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void* philo_routine(void *arg) 
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (actual_philo_dead(philo) == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
        
        printf("%ld %d is eating\n", time_now_ms() , philo->index_philo + 1);
        usleep(philo->time_to_eat * 1000);
        philo->last_time_eat = time_now_ms();
        philo->eat = 1;

        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);

        printf("%ld %d is sleeping\n",time_now_ms(),  philo->index_philo + 1);
        usleep(philo->time_to_sleep * 1000);

        printf("%ld %d is thinking\n",time_now_ms(),  philo->index_philo + 1);
    }
    return NULL;
}


int create_philosophers(t_dinner_table *dt)
{
    int i;
    
    i = 0;
    while (i < dt->nb_philo)
    {
        t_philosopher *philo = malloc(sizeof(t_philosopher)); 
        if(!philo)
            return (-1);
        philo->index_philo = i;
        philo->time_to_die = dt->time_to_die;
        philo->time_to_eat = dt->time_to_eat;
        philo->time_to_sleep = dt->time_to_sleep;
        philo->last_time_eat = time_now_ms();
        philo->l_fork = &dt->all_forks[i];
        philo->r_fork = &dt->all_forks[(i + 1) % dt->nb_philo];
        
        if (pthread_create(&dt->all_philo[i].thread, NULL, &philo_routine, (void *)philo) != 0)
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
        if (pthread_join(dt->all_philo[i].thread, NULL) != 0)
            return (perror("Failed to destroy philosophe"), -1);
        i++;
    }
    free(dt->all_philo);
    return (0);
}