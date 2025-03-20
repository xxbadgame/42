/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:29:51 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/20 14:42:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	actual_philo_dead(t_philosopher *philo)
{
	size_t	now;

	now = time_now_ms();
	pthread_mutex_lock(philo->eatex);
	if (now - philo->last_time_eat > philo->time_to_die && philo->eat == 0)
	{
		pthread_mutex_lock(philo->deadex);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->deadex);
		mutex_print("died", philo);
		pthread_detach(philo->thread);
		return (pthread_mutex_unlock(philo->eatex), 1);
	}
	pthread_mutex_unlock(philo->eatex);
	return (0);
}

int	check_all_philo_alive(t_dinner_table *dt)
{
	int	i;

	i = 0;
	while (i < dt->nb_philo)
	{
		if (actual_philo_dead(&dt->all_philo[i]))
			return (0);
		i++;
	}
	return (1);
}

int	everyone_full_eat(t_dinner_table *dt)
{
	int	i;
	int	eat_max;

	i = 0;
	eat_max = 0;
	if (dt->nb_each_philosopher_must_eat != -1)
	{
		while (i < dt->nb_philo)
		{
			pthread_mutex_lock(&dt->eatex);
			if (dt->all_philo[i].nb_meals >= dt->nb_each_philosopher_must_eat)
				eat_max++;
			pthread_mutex_unlock(&dt->eatex);
			i++;
		}
		if (eat_max >= dt->nb_each_philosopher_must_eat)
		{
			dt->full_eat_program = 1;
			return (1);
		}
	}
	return (0);
}
