/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:29:51 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/18 13:10:04 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

// basic thread check
int actual_philo_dead(t_philosopher *philo)
{
	size_t now;
	
	now = time_now_ms();
    if(philo->last_time_eat - now > philo->time_to_die && philo->eat == 0)
	{
		*philo->dead = 1;
		mutex_print("died", philo);
		return (1);
	}
	return (0);
}

// vérifier tous les threads car quand 1 meurt tout s'arrete en même temps
int check_all_philo_alive(t_dinner_table *dt)
{
	int i;

	i = 0;
	while (i < dt->nb_philo)
	{
		if (actual_philo_dead(&dt->all_philo[i]))
			return(0);
		i++;
	}
	return(1);
}

// vérifier tous les threads
int everyone_full_eat(t_dinner_table *dt)
{
	int i;

	i = 0;
	if (dt->nb_each_philosopher_must_eat != -1)
	{
		while (i < dt->nb_philo)
		{
			if(dt->all_philo[i].nb_meals != dt->nb_each_philosopher_must_eat)
				return (0);
			i++;
		}
	}
	return(1);
}
