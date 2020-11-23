/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosoph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:37:03 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/23 14:50:46 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		ft_init_struct(t_ptr *ptr, t_data *all, t_table *table)
{
	ptr->all = all;
	ptr->table = table;
	ptr->last_eat_time = my_get_time();
}

static int		ft_start_simulation(t_ptr *ptr, t_data *all, t_table *table)
{
	int		i;

	i = 0;
	while (i != all->number_of_philosophers)
	{
		ptr[i].philo_id = i;
		ft_init_struct(&ptr[i], all, table);
		ptr[i].status = pthread_create(&ptr[i].thread,
			NULL, life_style, &ptr[i]);
		if (ptr[i].status != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i != all->number_of_philosophers)
	{
		ptr[i].status = pthread_join(ptr[i].thread,
			(void**)&ptr[i].status_join);
		if (ptr[i].status != 0)
			return (1);
		i++;
	}
	return (0);
}

int				ft_philosoph(t_data *all)
{
	t_ptr	*ptr;
	t_table	table;

	all->start_time = my_get_time();
	all->philo_dead = 0;
	if (!(ptr = (t_ptr *)malloc(sizeof(t_ptr) * all->number_of_philosophers)))
		return (1);
	sem_unlink("fork");
	sem_unlink("text");
	sem_unlink("waiter");
	table.forks = sem_open("fork", O_CREAT, 0660, all->number_of_philosophers);
	table.text = sem_open("text", O_CREAT, 0660, 1);
	table.waiter = sem_open("waiter", O_CREAT, 0660, 1);
	if (ft_start_simulation(ptr, all, &table) == 1)
		return (1);	
	sem_close(table.forks);
	sem_close(table.text);
	sem_close(table.waiter);
	return (0);
}
