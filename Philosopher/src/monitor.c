/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:30:45 by yannis            #+#    #+#             */
/*   Updated: 2025/03/10 12:21:53 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void* monitor_routine(void *arg)
{
    t_dinner_table *dt = (t_dinner_table *)arg;
    int i;

    i = 0;
    if (dt->nb_each_philosopher_must_eat != -1)
    {
        while (i < dt->nb_each_philosopher_must_eat)
        {
            if (everyone_eat(dt) && check_all_philo_alive(dt))
                printf("fin du tour");
            i++;
        }
    } 
    else
    {
        while (1)
        {
            if (everyone_eat(dt) && check_all_philo_alive(dt))
                printf("fin du tour");
            i++;
        }
    } 
    printf("fin du programme");
    return NULL;
}


int create_monitor(t_dinner_table *dt)
{   
    dt->th_monitor = malloc(sizeof(pthread_t));
    if (!dt->th_monitor)
        return (-1);
    
    if (pthread_create(&dt->th_monitor[0], NULL, &monitor_routine, dt) != 0)
    {
        perror("Failed to create thread");
        free(dt->th_monitor);
        return (-1);
    }
    return (0);
}

int destroy_monitor(t_dinner_table *dt)
{
    if (pthread_join(dt->th_monitor[0], NULL) != 0)
        return (perror("Failed to destroy thread"), -1);
    free(dt->th_monitor);
    return (0);
}
