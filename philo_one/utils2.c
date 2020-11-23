/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:20:58 by atomatoe          #+#    #+#             */
/*   Updated: 2020/11/23 12:57:41 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_strlen(const char *b)
{
	int	a;

	a = 0;
	while (b[a] != '\0')
		a++;
	return (a);
}

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
