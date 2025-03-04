/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:29:51 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/04 12:48:56 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int dead_phil(t_dinner_table *dt, t_philosopher *philo)
{
	(void)philo;
    if(dt->philo_dead)
	{
		printf("philosophe is dead");
		return (-1);
	}
	return (1);
}