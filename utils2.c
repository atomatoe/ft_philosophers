/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:20:58 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/22 17:24:46 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	len(long n)
{
	int		d;

	d = 1;
	if (n < 0)
	{
		n = n * -1;
		d++;
	}
	while (n >= 10)
	{
		n = n / 10;
		d++;
	}
	return (d);
}

char		*ft_itoa(int nb)
{
	char	*str;
	int		i;
	int		f;
	long	n;

	n = nb;
	f = 0;
	i = len(n);
	if (!(str = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
		f = 1;
	}
	while ((i - f) > 0)
	{
		str[i - 1] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (str);
}
