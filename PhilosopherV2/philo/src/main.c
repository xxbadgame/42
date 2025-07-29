/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:45:07 by yannis            #+#    #+#             */
/*   Updated: 2025/07/28 22:50:05 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_time_philo_must_eat = ft_atoi(argv[5]);
	else
		data->nb_time_philo_must_eat = -1;
	data->is_dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->nb_philo);
	if (!data->forks)
		return (1);
	return (0);
}

static int	check_error_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc > 6)
		return (ft_putendl_fd("too many args", 2), 1);
	if (argc < 5)
		return (ft_putendl_fd("add 4 args minimum please", 2), 1);
	if (ft_atoi(argv[1]) == 0)
		return (ft_putendl_fd("1 philo minimum", 2), 1);
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			return (ft_putendl_fd("not number arg", 2), -1);
		if (ft_atoi(argv[i]) < 0)
			return (ft_putendl_fd("not positive value or loog number", 2), 1);
		if (ft_atoi(argv[1]) > 200)
			return (ft_putendl_fd("not test with more than 200 philo", 2), 1);
		if (i > 1 && i < 5 && ft_atoi(argv[i]) < 60)
			return (ft_putendl_fd("not test with less than 60ms", 2), 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (check_error_args(argc, argv) 
		|| init_data(&data, argv) 
		|| init_philo(&data))
		return (1);
	if (init_philo_threads(&data))
		return (1);
	destroy_philo(&data);
	destroy_mutex_and_free(&data, data.nb_philo - 1);
}