/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:59 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/10 19:30:56 by rchau            ###   ########.fr       */
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
		g_status.exit = 0;
		return (0);
	}
	else
	{
		write(2, "PATH did not found\n", 19);
		g_status.exit = 1;
		free(path);
		return (1);
	}
}
