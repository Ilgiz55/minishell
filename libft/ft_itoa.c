/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:31:39 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:31:40 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	reverse(char *s)
{
	char	c;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		c = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = c;
		i++;
	}
}

static void	strinrev(int n, char *s)
{
	size_t	i;
	int		sign;

	sign = n;
	i = 0;
	if (n == 0)
		s[i++] = '0';
	if (n < 0)
	{
		s[i++] = (n % 10) * -1 + '0';
		n = (n / 10) * -1;
	}
	while (n > 0)
	{
		s[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	k;

	k = len(n);
	s = malloc(sizeof(char) * k + 1);
	if (!s)
		return (NULL);
	strinrev(n, s);
	reverse(s);
	return (s);
}
