/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:29:51 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/17 14:22:38 by ynzue-es         ###   ########.fr       */
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

// vérifier tous les threads car quand 1 meurt tout s'arrete en même temps
int check_all_philo_alive(t_dinner_table *dt)
{
	int i;

	i = 0;
	while (i < dt->nb_philo)
	{
		if (dt->all_philo[i].dead == 1)
			return(0);
		i++;
	}
	printf("tous les philosphe sont en vie.");
	return(1);
}

// vérifier tous les threads
int everyone_eat(t_dinner_table *dt)
{
	int i;

	i = 0;
	if (dt->nb_each_philosopher_must_eat != -1)
	{
		while (i < dt->nb_philo)
		{
			if(dt->all_philo[i].eat != 1)
				return (0);
			i++;
		}
	}
	return(1);
}
