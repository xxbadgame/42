/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:30:45 by yannis            #+#    #+#             */
/*   Updated: 2025/03/04 11:29:49 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void* monitor_routine()
{
    while (1)
    {
        printf("monitor check \n");
        usleep(100000);
    }
    return NULL;
}


int create_monitor(t_dinner_table *dt)
{   
    dt->th_monitor = malloc(sizeof(pthread_t));
    if (!dt->th_monitor)
        return (-1);

    if (pthread_create(&dt->th_monitor[0], NULL, &monitor_routine, NULL) != 0)
        return (perror("Failed to create thread"), -1);
    return (0);
}

int destroy_monitor(t_dinner_table *dt)
{
    if (pthread_join(dt->th_monitor[0], NULL) != 0)
        return (perror("Failed to create thread"), -1);
    free(dt->th_monitor);
    return (0);
}
