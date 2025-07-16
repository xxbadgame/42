/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/16 15:19:15 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	init_philo_settings(t_philo_settings *philo_set, char **argv)
{
	philo_set->number_of_philo = ft_atoi(argv[1]);
	philo_set->time_to_die = ft_atoi(argv[2]);
	philo_set->time_to_eat = ft_atoi(argv[3]);
	philo_set->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo_set->nb_time_philo_must_eat = ft_atoi(argv[5]);
	else
		philo_set->nb_time_philo_must_eat = -1;
	philo_set->is_dead = 0;
	philo_set->forks = malloc(sizeof(pthread_mutex_t)
			* philo_set->number_of_philo);
	if (!philo_set->forks)
		return (-1);
	philo_set->time_start = time_now_ms();
	return (0);
}

static int	check_error_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc > 6)
		return (ft_putendl_fd("too many args", 2), -1);
	if (argc < 5)
		return (ft_putendl_fd("add 4 args minimum please", 2), -1);
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			return (ft_putendl_fd("not number arg", 2), -1);
		if (ft_atoi(argv[i]) < 0)
			return (ft_putendl_fd("not positive value or too loog number", 2),
				-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_settings	philo_set;
	t_global_mutex		mutex;
	t_philo				*philos;
	pthread_t			monitor_thread;

	if (check_error_args(argc, argv) == -1)
		return (1);
	if (init_philo_settings(&philo_set, argv) == -1)
		return (1);
	philos = malloc(sizeof(t_philo) * philo_set.number_of_philo);
	if (!philos)
		return (1);
	pthread_mutex_init(&mutex.print_mutex, NULL);
	pthread_mutex_init(&mutex.death_mutex, NULL);
	init_forks(&philo_set);
	if (init_philo_threads(&philo_set, &mutex, philos) == -1)
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philos) != 0)
	{
		ft_putendl_fd("Failed to create thread monitor", 2);
		return (destroy_all(&philo_set, &mutex, philos), -1);
	}
	pthread_join(monitor_thread, NULL);
	return (destroy_all(&philo_set, &mutex, philos), 0);
}
