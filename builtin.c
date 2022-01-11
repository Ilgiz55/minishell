/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:54:50 by rchau             #+#    #+#             */
/*   Updated: 2022/01/11 17:53:27 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_msh *msh, t_sup *sup)
{
	if (!ft_strncmp(msh->argv[0], "echo\0", 5))
		g_status = (ft_echo(msh->argv));
	else if (!ft_strncmp(msh->argv[0], "pwd\0", 4))
		g_status = (ft_pwd());
	else if (!ft_strncmp(msh->argv[0], "env\0", 4))
		g_status = (ft_env(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "export\0", 7))
		g_status = (ft_export(msh->argv, sup));
	else if (!ft_strncmp(msh->argv[0], "unset\0", 6))
		g_status = (ft_unset(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "cd\0", 3))
		g_status = (ft_cd(msh->argv, sup->env));
	else if (!ft_strncmp(msh->argv[0], "exit\0", 5))
		g_status = (ft_exit(msh->argv, sup->env));
	return (1);
}

int	ft_if_builtin(t_msh *msh)
{
	int		i;
	char	**b_com;

	b_com = (char **)malloc(sizeof(char *) * 7);
	b_com[0] = "echo";
	b_com[1] = "cd";
	b_com[2] = "pwd";
	b_com[3] = "export";
	b_com[4] = "unset";
	b_com[5] = "env";
	b_com[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(msh->argv[0], b_com[i], \
			ft_strlen(msh->argv[0]) | ft_strlen(b_com[i])))
		{
			free(b_com);
			return (1);
		}
		i++;
	}
	free(b_com);
	return (0);
}
