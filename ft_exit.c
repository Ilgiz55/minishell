/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:37 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 20:02:10 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_check(char *arg, char *com)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] == '-' || arg[i] == '+')
		{
			j = 1;
			i++;
		}
		if (!ft_isdigit(arg[i]) || i + j > 21)
			if (error_nar(com, arg))
				return (1);
	}
	return (0);
}

int	ft_exit(char **arg, char **env)
{
	int	i;

	if (arg[1] && arg[2])
		if (error_tma(arg[0]))
			return (1);
	if (arg[1])
	{
		if (exit_check(arg[1], arg[0]))
		{
			write (1, "exit\n", 5);
			exit (1);
		}
	}
	i = env_search_same("SHLVL", env);
	if (i >= 0 && env[i][6] != '2')
		env[i][6] = env[i][6] - 1;
	g_status = 0;
	if (arg[1])
		g_status = ft_atoi(arg[1]);
	write (1, "exit\n", 5);
	exit (g_status);
}
