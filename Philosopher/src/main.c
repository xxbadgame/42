/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/19 12:18:36 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int init_dinner_table(t_dinner_table *dt)
{
    dt->dead_program = 0;
    dt->full_eat_program = 0;
    if(pthread_mutex_init(&dt->printex, NULL) != 0)
        return (perror("Failed to create fork"), -1);
    if(pthread_mutex_init(&dt->eatex, NULL) != 0)
        return (perror("Failed to create fork"), -1);
    return (0);
}

int check_basic_args(int argc, char **argv, t_dinner_table *dt)
{
    if (argc == 5 || argc == 6)
    {
        dt->nb_philo = ft_atoi(argv[1]);
        dt->time_to_die = ft_atoi(argv[2]);
        dt->time_to_eat = ft_atoi(argv[3]);
        dt->time_to_sleep = ft_atoi(argv[4]);
        if (argc == 6)
            dt->nb_each_philosopher_must_eat = ft_atoi(argv[5]);
        else
            dt->nb_each_philosopher_must_eat = -1;
        return(1);
    }
    return(-1);
}

int main(int argc, char **argv)
{
    t_dinner_table dt;

    if (check_basic_args(argc, argv, &dt) == -1)
        return (-1);
    
    dt.all_philo = malloc(dt.nb_philo * sizeof(t_philosopher));
    dt.all_forks = malloc(dt.nb_philo * sizeof(pthread_mutex_t));
    
    init_dinner_table(&dt);
    create_forks(&dt);
    create_philosophers(&dt);
    create_monitor(&dt);

    destroy_philosophers(&dt);
    destroy_forks(&dt);
    destroy_monitor(&dt);

    return 0;
}
