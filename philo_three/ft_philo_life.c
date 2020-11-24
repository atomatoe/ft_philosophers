/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:43:21 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 15:52:10 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_philo_eat(t_ptr *filo)
{
	sem_wait(filo->table->waiter);
	sem_wait(filo->table->forks);
	ft_write_text(" has taken a fork\n", filo, 0);
	sem_wait(filo->table->forks);
	ft_write_text(" has taken a fork\n", filo, 0);
	sem_post(filo->table->waiter);
	ft_write_text(" is eating\n", filo, 0);
	sem_wait(filo->table->time);
	filo->last_eat_time = my_get_time();
	sem_post(filo->table->time);
	ft_usleep(filo->all->time_to_eat);
	sem_post(filo->table->forks);
	sem_post(filo->table->forks);
	ft_write_text(" is sleeping\n", filo, 0);
	ft_usleep(filo->all->time_to_sleep);
	ft_write_text(" is thinking\n", filo, 0);
}

static void	*ft_philo_dead(void *ptr)
{
	t_ptr		*filo_dead;

	filo_dead = ptr;
	while (1)
	{
		sem_wait(filo_dead->table->time);
		if ((my_get_time() - filo_dead->last_eat_time)
			> filo_dead->all->time_to_die)
			break ;
		sem_post(filo_dead->table->time);
	}
	sem_post(filo_dead->table->time);
	if (filo_dead->count_eat !=
		filo_dead->all->number_of_times_each_philosopher_must_eat)
		ft_write_text(" died\n", filo_dead, 1);
	filo_dead->all->philo_dead = 1;
	sem_post(filo_dead->table->death);
	return (NULL);
}

void		life_style(t_ptr *ptr)
{
	pthread_t	thread_dead;
	int			status_join;
	t_ptr		*filo;

	filo = ptr;
	pthread_create(&thread_dead, NULL, ft_philo_dead, filo);
	filo->count_eat = 0;
	while (1)
	{
		if (filo->count_eat ==
			filo->all->number_of_times_each_philosopher_must_eat)
			break ;
		ft_philo_eat(filo);
		if (filo->all->philo_dead == 1)
			break ;
		filo->count_eat++;
	}
	pthread_join(thread_dead, (void**)&status_join);
}
