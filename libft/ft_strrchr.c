/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:33:09 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:33:10 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	ch;

	str = (char *)s;
	i = ft_strlen(str);
	ch = (char)c;
	while (i >= 0)
	{
		if (str[i] == ch)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
