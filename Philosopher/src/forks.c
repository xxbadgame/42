/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:27:04 by yannis            #+#    #+#             */
/*   Updated: 2025/03/04 11:27:26 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int create_forks(t_dinner_table *dt)
{
    int i;

    i = 0;
    dt->forks = malloc(dt->nb_philo * sizeof(pthread_mutex_t));
    if (!dt->forks)
        return (-1);
    while (i < dt->nb_philo)
    {
        if(pthread_mutex_init(&dt->forks[i], NULL) != 0)
            return (perror("Failed to create fork"), -1);
        i++;
    }
    return (0);
}

int destroy_forks(t_dinner_table *dt)
{
    int i;

    i = 0;
    while (i < dt->nb_philo)
    {
        printf("destroy fork\n");
        if(pthread_mutex_destroy(&dt->forks[i]) != 0)
            return (perror("Failed to destroy fork"), -1);
        i++;
    }
    free(dt->forks);
    return (0);
}