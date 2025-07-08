/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/07/07 09:25:28 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	check_error_args(int argc)
{
	if (argc > 6)
		return (ft_putendl_fd("too many args", 2), -1);
	if (argc < 5)
		return (ft_putendl_fd("add 4 args minimum please", 2), -1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_settings philo_set;
	t_global_mutex mutex;
	t_philo *philos;
	pthread_t monitor_thread;

	if (check_error_args(argc) == -1)
		return (-1);

	philo_set.number_of_philo = ft_atoi(argv[1]);
	philo_set.time_to_die = ft_atoi(argv[2]);
	philo_set.time_to_eat = ft_atoi(argv[3]);
	philo_set.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo_set.nb_time_philo_must_eat = ft_atoi(argv[5]);
	else
		philo_set.nb_time_philo_must_eat = -1;
	philo_set.is_dead = 0;
	
	philos = malloc(sizeof(t_philo) * philo_set.number_of_philo);
	if (!philos)
		return (1);
	philo_set.forks = malloc(sizeof(pthread_mutex_t) * philo_set.number_of_philo);
	if (!philo_set.forks)
		return (1);
		
	pthread_mutex_init(&mutex.print_mutex, NULL);
	pthread_mutex_init(&mutex.death_mutex, NULL);
	init_forks(&philo_set);
	init_philo(&philo_set, &mutex, philos);
	pthread_create(&monitor_thread, NULL, monitor_routine, philos);
	
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&mutex.print_mutex);
	pthread_mutex_destroy(&mutex.death_mutex);
	free(philo_set.forks);
	free(philos);
	return (0);
}