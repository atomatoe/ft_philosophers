/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:43:21 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 01:16:45 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_philo_eat_even(t_ptr *filo)
{
	pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
	ft_write_text(" взял вилку\n", filo);
	pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
	ft_write_text(" взял вилку\n", filo);
	pthread_mutex_lock(&filo->table->time);
	filo->last_eat_time = my_get_time();
	pthread_mutex_unlock(&filo->table->time);
	ft_write_text(" начал кушать\n", filo);
	ft_usleep(filo->all->time_to_eat);
	pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
	pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
	ft_write_text(" лег спать\n", filo);
	ft_usleep(filo->all->time_to_sleep);
	ft_write_text(" думает\n", filo);
}

static void	ft_philo_eat_neven(t_ptr *filo)
{
	pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
	ft_write_text(" взял вилку\n", filo);
	pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
	ft_write_text(" взял вилку\n", filo);
	pthread_mutex_lock(&filo->table->time);
	filo->last_eat_time = my_get_time();
	pthread_mutex_unlock(&filo->table->time);
	ft_write_text(" начал кушать\n", filo);
	ft_usleep(filo->all->time_to_eat);
	pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
	pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
	ft_write_text(" лег спать\n", filo);
	ft_usleep(filo->all->time_to_sleep);
	ft_write_text(" думает\n", filo);
}

static void *ft_philo_dead(void *ptr)
{
	t_ptr *filo_dead;

	filo_dead = ptr;
	while(1)
	{
		pthread_mutex_lock(&filo_dead->table->time);
		if ((my_get_time() - filo_dead->last_eat_time) > filo_dead->all->time_to_die)
			break ;
		pthread_mutex_unlock(&filo_dead->table->time);
	}
	if(filo_dead->count_eat  != filo_dead->all->number_of_times_each_philosopher_must_eat)
		ft_write_text(" умер\n", filo_dead);
	filo_dead->all->philo_dead = 1;
	pthread_mutex_unlock(&filo_dead->table->time);
	return (NULL);
}

void		*life_style(void *ptr)
{
	pthread_t   thread_dead;
	int 		status;
	int			status_join;
	int 		i;
	t_ptr		*filo;

	filo = ptr;
	filo->left_fork = filo->philo_id;
	filo->right_fork = filo->philo_id - 1;
	if (filo->right_fork < 0)
		filo->right_fork = filo->all->number_of_philosophers - 1;
	status = filo->philo_id % 2;
	pthread_create(&thread_dead, NULL, ft_philo_dead, filo);
	filo->count_eat = 0;
	while (1)
	{
		if(filo->count_eat  == filo->all->number_of_times_each_philosopher_must_eat)
			break ;
		if (status == 1)
			ft_philo_eat_neven(filo);
		if (status != 1)
			ft_philo_eat_even(filo);
		if (filo->all->philo_dead == 1)
			break ;
		filo->count_eat ++;
	}
	status = pthread_join(thread_dead, (void**)&status_join);
	return (NULL);
}
