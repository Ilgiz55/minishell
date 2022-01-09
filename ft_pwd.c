/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubrey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:59 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/08 19:02:01 by laubrey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = malloc(sizeof(1024, 1));
	if (getcwd(path, 1024))
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
		g_status = 0;
		return (0);
	}
	else
	{
		write(2, "PATH did not found\n", 19);
		g_status = 1;
		free(path);
		return (1);
	}
}
