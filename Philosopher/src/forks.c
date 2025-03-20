/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:27:04 by yannis            #+#    #+#             */
/*   Updated: 2025/03/20 12:34:36 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	create_forks(t_dinner_table *dt)
{
	int	i;

	i = 0;
	while (i < dt->nb_philo)
	{
		if (pthread_mutex_init(&dt->all_forks[i], NULL) != 0)
			return (perror("Failed to create fork"), -1);
		i++;
	}
	return (0);
}

int	destroy_forks(t_dinner_table *dt)
{
	int i;

	i = 0;
	while (i < dt->nb_philo)
	{
		if (pthread_mutex_destroy(&dt->all_forks[i]) != 0)
			return (perror("Failed to destroy fork"), -1);
		i++;
	}
	free(dt->all_forks);
	return (0);
}