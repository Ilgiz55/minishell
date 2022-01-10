/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:33:06 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:33:07 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	s2_len;
	char	*s;

	s = (char *)s1;
	s_len = ft_strlen(s);
	s2_len = ft_strlen(s2);
	if (s2_len == 0)
		return (s);
	if (s_len < s2_len || n < s2_len)
		return (NULL);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s2[j] && s2[j] == s[i + j] && i + j < n)
			j++;
		if (j == s2_len)
			return (&s[i]);
		i++;
	}
	return (NULL);
}
