/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:32:55 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:32:56 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	slen;

	if (!src)
		return (0);
	slen = ft_strlen(src);
	if (n && dest)
	{
		while (*src && n-- > 1)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (slen);
}
