/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:33 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/19 11:09:57 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_dinner_table
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat_by_phil;
    int philo_dead;
    pthread_mutex_t *forks;
    pthread_t *th_philo;
    pthread_t *th_monitor;  
} t_dinner_table ;

typedef struct s_philosopher {
    int index_phil;
    t_dinner_table *dt;
} t_philosopher;

// forks
int     create_forks(t_dinner_table *dt);
int     destroy_forks(t_dinner_table *dt);

// philosophers
void*   philo_routine(void *arg);
int     create_philosophers(t_dinner_table *dt);
int     destroy_philosophers(t_dinner_table *dt);

// monitor
void*   monitor_routine();
int     create_monitor(t_dinner_table *dt);
int     destroy_monitor(t_dinner_table *dt);


