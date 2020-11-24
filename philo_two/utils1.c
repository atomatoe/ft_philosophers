/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:15:31 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 15:59:49 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_usleep(long sec)
{
	long	fix_time;

	fix_time = my_get_time();
	while (my_get_time() - fix_time < sec)
		usleep(1);
}

void	ft_write_text(char *s, t_ptr *filo, int flag)
{
	long	times;
	char	*text;
	char	*s1;
	char	*s2;
	char	*s3;

	sem_wait(filo->table->text);
	sem_wait(filo->table->time);
	times = my_get_time();
	sem_post(filo->table->time);
	s1 = ft_itoa(times - filo->all->start_time);
	s2 = ft_strjoin(s1, " Philosopher ");
	free(s1);
	s1 = ft_itoa(filo->philo_id + 1);
	s3 = ft_strjoin(s2, s1);
	ft_free_two(s1, s2);
	text = ft_strjoin(s3, s);
	free(s3);
	sem_wait(filo->table->death_philo);
	if (filo->all->philo_dead != 1)
		ft_putstr(text);
	free(text);
	if (flag == 0)
		sem_post(filo->table->death_philo);
	sem_post(filo->table->text);
}

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

int		ft_atoi(const char *nptr)
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

long	my_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
