/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:27:04 by yannis            #+#    #+#             */
/*   Updated: 2025/02/17 12:49:46 by yannis           ###   ########.fr       */
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
        pthread_mutex_init(&dt->forks[i++], NULL);
    return (0);
}

int destroy_forks(t_dinner_table *dt)
{
    int i;

    i = 0;
    while (i < dt->nb_philo)
    {
        pthread_mutex_destroy(&dt->forks[i]);
        free(&dt->forks[i++]);
    }
    free(dt->forks);
    return (0);
}