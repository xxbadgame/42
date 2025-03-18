/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:46 by yannis            #+#    #+#             */
/*   Updated: 2025/03/18 13:13:25 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void* philo_routine(void *arg) 
{
    t_philosopher *philo;
    
    philo = (t_philosopher *)arg;
    while (*philo->dead != 1)
    {
        pthread_mutex_lock(philo->l_fork);
        mutex_print("has taken a fork", philo);
        pthread_mutex_lock(philo->r_fork);
        mutex_print("has taken a fork", philo);
    
        mutex_print("is eating", philo);
        philo->eat = 1;
        usleep(philo->time_to_eat * 1000);
        philo->last_time_eat = time_now_ms();
        philo->nb_meals++;
        philo->eat = 0;

        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);

        mutex_print("is sleeping", philo);
        usleep(philo->time_to_sleep * 1000);
        
        mutex_print("is thinking", philo);
    }
    return NULL;
}

int init_data(t_philosopher *philo, t_dinner_table *dt, int i)
{
    philo->index_philo = i + 1;
    philo->time_to_die = dt->time_to_die;
    philo->time_to_eat = dt->time_to_eat;
    philo->time_to_sleep = dt->time_to_sleep;
    philo->last_time_eat = time_now_ms();
    philo->dead = &dt->dead_program;
    philo->nb_meals = 0;
    philo->eat = 0;
    philo->l_fork = &dt->all_forks[i];
    philo->r_fork = &dt->all_forks[(i + 1) % dt->nb_philo];
    philo->printex = malloc(sizeof(pthread_mutex_t));
    if(pthread_mutex_init(&philo->printex[0], NULL) != 0)
            return (perror("Failed to create fork"), -1);
    return (0);
}

int create_philosophers(t_dinner_table *dt)
{
    int i;
    
    i = 0;
    dt->dead_program = 0;
    while (i < dt->nb_philo)
    {
        t_philosopher *philo = malloc(sizeof(t_philosopher)); 
        if(!philo)
            return (-1);
        
        init_data(philo, dt, i);
        
        if (pthread_create(&dt->all_philo[i].thread, NULL, &philo_routine, (void *)philo) != 0)
        {
            perror("Failed to create philospher");
            free(dt->th_monitor);
            return (-1);
        }
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