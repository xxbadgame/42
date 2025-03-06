/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/06 12:22:23 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"


int check_basic_args(int argc, char **argv, t_dinner_table *dt)
{
    if (argc == 4 || argc ==5)
    {
        if (argv[1] == 1)
        {
            printf("philospher is dead");
            return(-1);
        }
        dt->nb_philo = ft_atoi(argv[1]);
        dt->time_to_die = ft_atoi(argv[2]);
        dt->time_to_eat = ft_atoi(argv[3]);
        dt->time_to_sleep = ft_atoi(argv[4]);
        if (argv == 5)
            dt->nb_each_philosopher_must_eat = ft_atoi(argv[5]);
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
    
    create_forks(&dt);
    create_philosophers(&dt);
    //create_monitor(&dt);

    
    destroy_philosophers(&dt);
    destroy_forks(&dt);
    //destroy_monitor(&dt);

    return 0;
}
