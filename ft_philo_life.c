/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:43:21 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/22 18:06:19 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_philo_eat_even(t_ptr *filo)
{
	ft_write_text(" думает\n", filo);
	pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
	pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
	ft_write_text(" взял вилку\n", filo);
	ft_write_text(" начал кушать\n", filo);
	ft_usleep(filo->all->time_to_eat);
	ft_write_text(" покушал\n", filo);
	pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
	pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
	ft_write_text(" лег спать\n", filo);
	ft_usleep(filo->all->time_to_sleep);
}

static void	ft_philo_eat_neven(t_ptr *filo)
{
	ft_write_text(" думает\n", filo);
	pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
	pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
	ft_write_text(" взял вилку\n", filo);
	ft_write_text(" начал кушать\n", filo);
	ft_usleep(filo->all->time_to_eat);
	ft_write_text(" покушал\n", filo);
	pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
	pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
	ft_write_text(" лег спать\n", filo);
	ft_usleep(filo->all->time_to_sleep);
}

void		*life_style(void *ptr)
{
	int		status;
	t_ptr	*filo;

	filo = ptr;
	filo->left_fork = filo->philo_id;
	filo->right_fork = filo->philo_id - 1;
	if (filo->right_fork < 0)
		filo->right_fork = filo->all->number_of_philosophers - 1;
	status = filo->philo_id % 2; // 0 - четный 1 - нечетный

	while (1)
	{
		if (status == 1)
			ft_philo_eat_neven(filo);
		else
			ft_philo_eat_even(filo);
	}
	return (NULL);
}
