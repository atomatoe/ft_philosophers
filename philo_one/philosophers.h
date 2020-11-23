/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:46:00 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/23 11:55:21 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct	s_table
{
    pthread_mutex_t *forks;
    pthread_mutex_t time;
    pthread_mutex_t text;
    //pthread_mutex_t dead;
}				t_table;

typedef struct	s_data
{
    int         number_of_philosophers; // количество философ
    long        time_to_die;   // время до смерти миллисекунды
    long        time_to_eat;    // время на покушать миллисекунды
    long        time_to_sleep;  // время поспать миллисекунды
    long        start_time;
    int         number_of_times_each_philosopher_must_eat;  // сколько раз могут всего покушать
    int         philo_dead;
}				t_data;

typedef struct	s_ptr
{
    pthread_t   thread;
    int         philo_id;
    int         status;
    int         status_join;
    int         left_fork;
    int         right_fork;
    long        last_eat_time;
    int         count_eat;
    t_data      *all;
    t_table     *table;
}				t_ptr;


int		ft_atoi(const char *nptr);
int		ft_philosoph(t_data *all);
void	ft_usleep(long sec);
void	*life_style(void *ptr);
void	ft_putstr(char *s);
void	ft_write_text(char *s, t_ptr *filo);
long	my_get_time(void);
char	*ft_itoa(int nb);

#endif