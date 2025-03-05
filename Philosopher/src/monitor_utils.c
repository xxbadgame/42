/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:29:51 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/05 17:54:37 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

// basic thread check
int actual_philo_dead(t_philosopher *philo)
{
	struct timeval time;
	size_t now;
	
	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
    if(philo->last_time_eat - now > philo->time_to_die && philo->eat == 0)
	{
		philo->dead = 1;
		printf("philo is dead\n");
		return (1);
	}
	return (0);
}

// monitor check all
/*
int check_all_philo_alive(t_dinner_table *dt)
{
	int i;

	i = 0;
	while (i < dt->nb_philo)
	{
		if (dt->all_philo[i].dead == 1)
			return(-1);
	}
	printf("tous les philosphe sont en vie.");
}

// ici
int everyone_eat(t_dinner_table *dt, t_philosopher *philo)
{
	int i;
	int most_h;

	i = 0;
	most_h = i;
	while (dt->th_philo[i])
	{
		if (dt->th_philo[i]->eat)
	}	
}
*/