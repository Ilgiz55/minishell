/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:32:42 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:37:01 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	char	ch;

	p = (char *)s;
	ch = (char)c;
	while (*p)
	{
		if (*p == ch)
			return (p);
		p++;
	}
	if (!ch)
		return (p);
	return (NULL);
}
