/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosoph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:37:03 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 01:17:30 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		ft_init_struct(t_ptr *ptr, t_data *all, t_table *table)
{
	ptr->all = all;
	ptr->table = table;
	ptr->last_eat_time = my_get_time();
}

static void		ft_start_simulation(t_ptr *ptr, t_data *all, t_table *table)
{
	int		i;
	int		philos[all->number_of_philosophers];
	pid_t	philo;

	i = 0;
	all->start_time = my_get_time();
	while (i < all->number_of_philosophers)
	{
		philo = fork();
		if(philo == 0)
		{
			ptr[i].philo_id = i;
			ft_init_struct(&ptr[i], all, table);
			life_style(&ptr[i]);
			exit(0);
		}
		else
			philos[i++] = philo;
	}
	i = 0;
	sem_wait(table->death);
	while(i < all->number_of_philosophers)
		kill(philos[i++], SIGKILL);
}

int				ft_philosoph(t_data *all)
{
	t_ptr	*ptr;
	t_table	table;

	all->philo_dead = 0;
	if (!(ptr = (t_ptr *)malloc(sizeof(t_ptr) * all->number_of_philosophers)))
		return (1);
	sem_unlink("fork");
	sem_unlink("text");
	sem_unlink("waiter");
	sem_unlink("death");
	sem_unlink("death_philo");
	if ((table.forks = sem_open("forks", O_CREAT, 0660, all->number_of_philosophers)) == SEM_FAILED)
		return (1);
	if ((table.text = sem_open("text", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((table.waiter = sem_open("waiter", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	if ((table.death_philo = sem_open("death_philo", O_CREAT, NULL, 1)) == SEM_FAILED)
		return (1);
	ft_start_simulation(ptr, all, &table);
	sem_close(table.forks);
	sem_close(table.text);
	sem_close(table.waiter);
	sem_close(table.death);
	sem_close(table.death_philo);
	return (0);
}
