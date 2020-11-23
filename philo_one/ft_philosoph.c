/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosoph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:37:03 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 02:25:04 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	int		i;
	t_ptr	*ptr;
	t_table	table;

	all->start_time = my_get_time();
	all->philo_dead = 0;
	if (!(table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* all->number_of_philosophers)))
		return (1);
	if (!(ptr = (t_ptr *)malloc(sizeof(t_ptr) * all->number_of_philosophers)))
		return (1);
	pthread_mutex_init(&table.text, NULL);
	pthread_mutex_init(&table.time, NULL);
	i = 0;
	while (i != all->number_of_philosophers)
	{
		pthread_mutex_init(&table.forks[i], NULL);
		i++;
	}
	if (ft_start_simulation(ptr, all, &table) == 1)
		return (1);
	return (0);
}
