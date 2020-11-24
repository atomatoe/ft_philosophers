/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:20:58 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/24 02:53:40 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		ft_len(int n)
{
	int size;

	size = 1;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n >= 10)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char			*ft_itoa(long nb)
{
	int		i;
	char	*res;

	i = ft_len(nb);
	if (!(res = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	res[i--] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb >= 10)
	{
		res[i--] = nb % 10 + '0';
		nb /= 10;
	}
	res[i] = nb + '0';
	return (res);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
	{
		if (src)
			return (ft_strlen(src));
		return (0);
	}
	if (!size)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	len2;

	i = 0;
	len = ft_strlen(dst);
	len2 = ft_strlen(src);
	if (size <= len)
		return (size + len2);
	while (dst[i] != '\0' && i < (size - 1))
		i++;
	while (*src && i < size - 1)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	return (len + len2);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	size_t		size1;
	size_t		size2;

	if (!s2 || !s1)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!(s3 = (char*)malloc(sizeof(char) * (size1 + size2 + 1))))
		return (NULL);
	ft_strlcpy(s3, s1, (size1 + 1));
	ft_strlcat(s3, s2, (size1 + size2 + 1));
	return (s3);
}
