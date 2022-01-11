/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:00:11 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 17:55:21 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_currpwd(char **env)
{
	char	*sup;

	sup = malloc(sizeof(char) * 1024);
	if (getcwd(sup, 1024))
		cd_chdirs(sup, env);
	else
	{
		write(2, "PATH did not found\n", 19);
		g_status = 1;
	}
	free(sup);
}

void	cd_prevpwd(char **env)
{
	char	*sup;
	char	*temp;

	sup = malloc(sizeof(char) * 1024);
	if (getcwd(sup, 1024))
	{
		temp = ft_strrchr(sup, '/');
		while (*temp)
		{
			*temp = '\0';
			temp++;
		}
		if (sup != '\0')
			cd_chdirs(sup, env);
	}
	else
	{
		write(2, "PATH did not found\n", 19);
		g_status = 1;
	}
	free(sup);
}

void	cd_oldpwd(char **env)
{
	char	*sup;
	int		i;

	i = env_search_same("OLDPWD\0", env);
	if (i >= 0 && env[i][7] != '\0')
	{
		sup = ft_substr(env[i], 7, ft_strlen(&env[i][7]));
		cd_chdirs(sup, env);
		free(sup);
	}
	else if (i >= 0 && env[i][7] == '\0')
	{
		write(1, "\n", 1);
		cd_currpwd(env);
	}
	else
	{
		g_status = 1;
		write(1, "cd: OLDPWD not set\n", 19);
	}
}

void	cd_home(char **env)
{
	char	*sup;
	int		i;

	i = env_search_same("HOME", env);
	if (i >= 0 && env[i][5] != '\0')
	{
		sup = ft_substr(env[i], 5, ft_strlen(&env[i][5]));
		cd_chdirs(sup, env);
		free(sup);
	}
	else if (i >= 0 && env[i][5] == '\0')
		cd_currpwd(env);
	else
	{
		g_status = 1;
		write(1, "cd: HOME not set\n", 17);
	}
}

int	ft_cd(char **arg, char **env)
{
	if (!arg[1])
		cd_home(env);
	else if (!ft_strncmp(arg[1], "..\0", 3))
		cd_prevpwd(env);
	else if (!ft_strncmp(arg[1], ".\0", 2))
		cd_currpwd(env);
	else if (!ft_strncmp(arg[1], "-\0", 2))
		cd_oldpwd(env);
	else
		cd_chdirs(arg[1], env);
	return (0);
}
