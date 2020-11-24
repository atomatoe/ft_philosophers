/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:46:00 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 15:58:14 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct		s_table
{
	pthread_mutex_t *forks;
	pthread_mutex_t time;
	pthread_mutex_t text;
	pthread_mutex_t death;
}					t_table;

typedef struct		s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				number_of_times_each_philosopher_must_eat;
	int				philo_dead;
}					t_data;

typedef struct		s_ptr
{
	pthread_t		thread;
	int				philo_id;
	int				status;
	int				status_join;
	int				left_fork;
	int				right_fork;
	long			last_eat_time;
	int				count_eat;
	t_data			*all;
	t_table			*table;
}					t_ptr;

int					ft_atoi(const char *nptr);
int					ft_philosoph(t_data *all);
void				ft_usleep(long sec);
void				*life_style(void *ptr);
void				ft_putstr(char *s);
void				ft_write_text(char *s, t_ptr *filo, int flag);
void				ft_free_two(char *s1, char *s2);
long				my_get_time(void);
char				*ft_itoa(long nb);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *b);

#endif
