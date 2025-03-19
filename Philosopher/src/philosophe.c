/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:46 by yannis            #+#    #+#             */
/*   Updated: 2025/03/19 18:03:42 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

/*
static int safe_end_checker(t_philosopher *philo)
{
    pthread_mutex_lock(philo->deadex);
    if (*philo->dead != 1 && *philo->everyone_eat != 1)
        return (0);
    pthread_mutex_unlock(philo->deadex);
    return (1);
}
*/

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (*philo->dead != 1 && *philo->everyone_eat != 1)
	{
        r_eat(philo);
        r_sleep(philo);
        r_think(philo);
	}
	return (NULL);
}

static int	init_data_philo(t_philosopher *philo, t_dinner_table *dt, int i)
{
	philo->index_philo = i;
	philo->time_to_die = dt->time_to_die;
	philo->time_to_eat = dt->time_to_eat;
	philo->time_to_sleep = dt->time_to_sleep;
	philo->last_time_eat = time_now_ms();
	philo->dead = &dt->dead_program;
	philo->everyone_eat = &dt->full_eat_program;
	philo->nb_meals = 0;
	philo->eat = 0;
	philo->printex = &dt->printex;
	philo->eatex = &dt->eatex;
    philo->deadex = &dt->deadex;
	philo->l_fork = &dt->all_forks[i];
	philo->r_fork = &dt->all_forks[(i + 1) % dt->nb_philo];
	return (0);
}

int	create_philosophers(t_dinner_table *dt)
{
	int	i;

	i = 0;
	while (i < dt->nb_philo)
	{
		init_data_philo(&dt->all_philo[i], dt, i);
		if (pthread_create(&dt->all_philo[i].thread, NULL, &philo_routine,
				(void *)&dt->all_philo[i]) != 0)
			return (perror("Failed to create philospher"), -1);
		i++;
	}
	return (0);
}

int	destroy_philosophers(t_dinner_table *dt)
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