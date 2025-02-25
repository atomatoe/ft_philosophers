/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:46:00 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 15:59:22 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct	s_table
{
	sem_t		*forks;
	sem_t		*time;
	sem_t		*text;
	sem_t		*waiter;
	sem_t		*death_philo;
}				t_table;

typedef struct	s_data
{
	int			number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		start_time;
	int			number_of_times_each_philosopher_must_eat;
	int			philo_dead;
}				t_data;

typedef struct	s_ptr
{
	int			philo_id;
	int			status;
	int			status_join;
	long		last_eat_time;
	int			count_eat;
	t_data		*all;
	t_table		*table;
}				t_ptr;

int				ft_atoi(const char *nptr);
int				ft_philosoph(t_data *all);
void			ft_usleep(long sec);
void			*life_style(void *ptr);
void			ft_putstr(char *s);
void			ft_write_text(char *s, t_ptr *filo, int flag);
void			ft_free_two(char *s1, char *s2);
long			my_get_time(void);
char			*ft_itoa(long nb);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *b);

#endif
