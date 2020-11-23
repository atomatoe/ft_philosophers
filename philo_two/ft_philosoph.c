/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosoph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:37:03 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 02:44:58 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		ft_init_struct(t_ptr *ptr, t_data *all, t_table *table)
{
	ptr->all = all;
	ptr->table = table;
	ptr->last_eat_time = my_get_time();
}

static int		ft_start_simulation(t_ptr *ptr, t_data *all, t_table *table)
{
	int			i;
	pthread_t	thread_philo[all->number_of_philosophers];

	i = 0;
	all->start_time = my_get_time();
	while (i != all->number_of_philosophers)
	{
		ptr[i].philo_id = i;
		ft_init_struct(&ptr[i], all, table);
		ptr[i].status = pthread_create(&thread_philo[i],
			NULL, life_style, &ptr[i]);
		if (ptr[i].status != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i != all->number_of_philosophers)
	{
		ptr[i].status = pthread_join(thread_philo[i],
			(void**)&ptr[i].status_join);
		if (ptr[i].status != 0)
			return (1);
		i++;
	}
	return (0);
}

static int		ft_init_sem(t_table *table, t_data *all)
{
	sem_unlink("forks");
	sem_unlink("text");
	sem_unlink("waiter");
	sem_unlink("death_philo");
	if ((table->forks = sem_open("forks", O_CREAT, 0660,
		all->number_of_philosophers)) == SEM_FAILED)
		return (1);
	if ((table->text = sem_open("text", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((table->waiter = sem_open("waiter", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((table->death_philo = sem_open("death_philo",
		O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	return (0);
}

int				ft_philosoph(t_data *all)
{
	t_ptr	ptr[all->number_of_philosophers];
	t_table	table;

	all->philo_dead = 0;
	ft_init_sem(&table, all);
	if (ft_start_simulation(ptr, all, &table) == 1)
		return (1);
	sem_close(table.forks);
	sem_close(table.text);
	sem_close(table.waiter);
	sem_close(table.death_philo);
	return (0);
}
