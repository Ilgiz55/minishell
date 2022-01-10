/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:31:08 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:36:20 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	res;
	long	max;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	max = 214748364;
	while (str[i] && (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || \
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((res > max || (res == max && (str[i] - '0') > 7)) && sign == 1)
			return (-1);
		if ((res > max || (res == max && (str[i] - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
	return ((int)res * sign);
}
