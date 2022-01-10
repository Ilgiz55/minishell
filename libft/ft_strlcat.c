/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:32:52 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:32:53 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dlen;
	size_t	slen;
	size_t	reslen;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (dlen < n)
		reslen = dlen + slen;
	else
		reslen = n + slen;
	dest += dlen;
	if (n > dlen)
	{
		n -= dlen;
		while (*src && n-- > 1)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (reslen);
}
