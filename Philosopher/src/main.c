/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/05 17:55:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"


// ici check args
int main()
{
    t_dinner_table dt;
    dt.nb_philo = 2;
    if (dt.nb_philo == 1)
    {
        printf("philo is dead\n");
        return(-1);
    }
        
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
