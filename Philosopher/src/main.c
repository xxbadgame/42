/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:56 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/04 12:32:07 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int main()
{
    t_dinner_table dt;
    
    dt.nb_philo = 4;
    dt.time_to_die = 800;
    dt.time_to_eat = 200;
    dt.time_to_sleep = 200;

    create_forks(&dt);
    create_philosophers(&dt);
    //create_monitor(&dt);

    //destroy_forks(&dt);
    destroy_philosophers(&dt);
    //destroy_monitor(&dt);

    return 0;
}
