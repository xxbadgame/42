/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:33 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/12 12:39:05 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_dinner_table
{
    int nb_phil;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat_by_phil;
    pthread_mutex_t *forks;    
} t_dinner_table ;

typedef struct s_philosopher {
    int index_phil;
    t_dinner_table *dt;
} t_philosopher;

int init_forks(t_dinner_table *dt);
int destroy_forks(t_dinner_table *dt);