/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:27 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 20:02:06 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv, char **env)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		error_nsfod("env", argv[1]);
		return (127);
	}
	else
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
			{
				write(1, env[i], ft_strlen(env[i]));
				write(1, "\n", 1);
			}
			i++;
		}
	}
	return (0);
}
