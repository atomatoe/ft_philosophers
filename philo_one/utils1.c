/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:15:31 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/22 23:10:20 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_usleep(long sec)
{
	long fix_time;

	fix_time = my_get_time();
	while (my_get_time() - fix_time < sec)
		usleep(10);
}

void	ft_write_text(char *s, t_ptr *filo)
{
	long times;

	pthread_mutex_lock(&filo->table->text);
	if (filo->all->philo_dead != 1)
	{
		times = my_get_time();
		ft_putstr(ft_itoa(times - filo->all->start_time));
		ft_putstr(" Философ ");
		ft_putstr(ft_itoa(filo->philo_id));
		ft_putstr(s);
	}
	pthread_mutex_unlock(&filo->table->text);
}

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	g;
	int		minus;
	char	*str;

	i = 0;
	g = 0;
	minus = 1;
	str = (char *)nptr;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		g = g * 10 + (str[i] - '0');
		i++;
	}
	return (g * minus);
}

long my_get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}