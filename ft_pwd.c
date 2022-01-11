/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:59 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 20:02:16 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * 1024);
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
