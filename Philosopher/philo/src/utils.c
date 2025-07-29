/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:19:06 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/28 23:20:59 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	wait_check_dead(t_philo *philo, size_t wait_time)
{
	size_t	time;

	time = time_now_ms();
	while (time_now_ms() - time < wait_time)
	{
		if (is_dead(philo) == 1)
			return (-1);
		usleep(10);
	}
	return (0);
}
