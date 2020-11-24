/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:46:01 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 16:00:15 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			ft_free_two(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

size_t			ft_strlen(const char *b)
{
	int	a;

	a = 0;
	while (b[a] != '\0')
		a++;
	return (a);
}

static int		ft_parse_param(char **argv, t_data *all)
{
	all->number_of_times_each_philosopher_must_eat = -1;
	all->number_of_philosophers = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (all->number_of_philosophers == 0 || all->time_to_die == 0 ||
		all->time_to_eat == 0 || all->time_to_sleep == 0)
		return (1);
	if (all->number_of_philosophers < 2)
	{
		ft_putstr("please, give me fork, i'm die...d...\n");
		return (1);
	}
	return (0);
}

static int		ft_check_param(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_data all;

	if (argc < 5 || argc > 6)
		return (-1);
	if (ft_check_param(argv) == 1)
		return (-1);
	if (ft_parse_param(argv, &all) == 1)
		return (-1);
	if (ft_philosoph(&all) == 1)
		return (-1);
	return (0);
}
