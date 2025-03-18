/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:33 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/03/18 13:11:18 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

// philo character
typedef struct s_philosopher 
{
    pthread_t thread;
    int index_philo;
    
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    
    size_t last_time_eat;
    int *dead;
    int nb_meals;
    int eat;
    
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *printex;

}   t_philosopher;

// global data
typedef struct s_dinner_table
{
    int nb_philo;
    int time_now;
    int dead_program;

    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    int nb_each_philosopher_must_eat;
    
    t_philosopher   *all_philo;
    pthread_mutex_t *all_forks;
    pthread_t       *th_monitor;
    
}   t_dinner_table;


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
int     actual_philo_dead(t_philosopher *philo);
int     check_all_philo_alive(t_dinner_table *dt);
int     everyone_full_eat(t_dinner_table *dt);


// utils
size_t time_now_ms();
void mutex_print(char *str, t_philosopher *philo);

