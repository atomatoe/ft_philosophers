/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:43:21 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/23 14:50:52 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_philo_eat(t_ptr *filo)
{
	sem_wait(filo->table->waiter);
	sem_wait(filo->table->forks);
	ft_write_text(" взял вилку\n", filo);
	sem_wait(filo->table->forks);
	ft_write_text(" взял вилку\n", filo);
	sem_post(filo->table->waiter);
	ft_write_text(" начал кушать\n", filo);
	filo->last_eat_time = my_get_time();
	ft_write_text(" кушает\n", filo);
	ft_usleep(filo->all->time_to_eat);
	sem_post(filo->table->forks);
	sem_post(filo->table->forks);
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
		sem_wait(filo_dead->table->time);
		if ((my_get_time() - filo_dead->last_eat_time) > filo_dead->all->time_to_die)
			break ;
		sem_post(filo_dead->table->time);
	}
	if(filo_dead->count_eat  != filo_dead->all->number_of_times_each_philosopher_must_eat)
		ft_write_text(" умер\n", filo_dead);
	filo_dead->all->philo_dead = 1;
	sem_post(filo_dead->table->time);
	return (NULL);
}

void		*life_style(void *ptr)
{
	pthread_t   thread_dead;
	int			status_join;
	int 		i;
	t_ptr		*filo;

	filo = ptr;
	pthread_create(&thread_dead, NULL, ft_philo_dead, filo);
	filo->count_eat = 0;
	while (1)
	{
		if(filo->count_eat  == filo->all->number_of_times_each_philosopher_must_eat)
			break ;
		ft_philo_eat(filo);
		if (filo->all->philo_dead == 1)
			break ;
		filo->count_eat ++;
	}
	pthread_join(thread_dead, (void**)&status_join);
	return (NULL);
}