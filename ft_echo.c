/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:15 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 20:02:01 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argv[1] && !ft_strncmp(argv[1], "-n\0", 3))
		i++;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			write(1, &argv[i][j], 1);
		if (argv[i + 1])
			write(1, " ", 1);
	}
	if (!argv[1] || ft_strncmp(argv[1], "-n\0", 3))
		write(1, "\n", 1);
	return (0);
}
