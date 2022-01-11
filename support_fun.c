/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:03:15 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 20:03:04 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mass(char **mass)
{
	int	i;

	i = 0;
	while (mass[i])
		i++;
	while (--i >= 0)
	{
		free(mass[i]);
		mass[i] = NULL;
	}
	free(mass);
	mass = NULL;
}

void	one_mas_fr_two(t_sup *sup, char *from)
{
	int		i;
	char	**mass;

	i = 0;
	while (sup->env[i])
	{
		i++;
	}
	mass = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((sup->env)[i])
	{
		mass[i] = ft_strdup((sup->env)[i]);
		i++;
	}
	mass[i] = malloc(sizeof(char) * (ft_strlen(from)));
	ft_memcpy(mass[i], from, ft_strlen(from));
	free_mass(sup->env);
	mass[i + 1] = NULL;
	sup->env = mass;
}

int	env_search_same(char *arg, char **env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (arg[k] != '=' && arg[k])
		k++;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
		{
			j++;
		}
		if (!ft_memcmp(arg, env[i], j) && k == j)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	cd_chdirs(char *sup, char **env)
{
	int		i;
	int		j;
	char	*oldpwd;

	oldpwd = malloc(sizeof(char) * 1024);
	getcwd(oldpwd, 1024);
	if (chdir(sup))
		g_status = error_nsfod("cd", sup);
	else
	{
		i = env_search_same("OLDPWD\0", env);
		if (i >= 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		j = env_search_same("PWD\0", env);
		if (j >= 0)
		{
			free(env[j]);
			env[j] = ft_strjoin("PWD=\0", sup);
		}
		g_status = 0;
	}
	free(oldpwd);
}
