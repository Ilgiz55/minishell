/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubrey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:01:47 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/08 19:01:50 by laubrey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_sort(char **env)
{
	int		i;
	int		j;
	int		k;
	char	**env_sup;
	char	*check;

	i = 0;
	while (env[i])
		i++;
	env_sup = (char **)malloc(sizeof(char *) * (i + 1));
	env_sup[i] = NULL;
	while (--i >= 0)
	{
		check = ft_strdup(env[i]);
		k = -1;
		j = 0;
		while (env[++k])
			if (ft_strncmp(check, env[k], ft_strlen(env[i]) + 1) > 0)
				j++;
		env_sup[j] = check;
	}
	print_quotes(env_sup);
	free_mass(env_sup);
	return (0);
}

void	print_quotes(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		write(1, "declare -x ", 11);
		while (env[i] && env[i][++j] != '=' && env[i][j] != '\0')
			write(1, &env[i][j], 1);
		if (env[i] && env[i][j] == '=')
		{
			write(1, "=\"", 2);
			while (env[i] && env[i] != NULL && env[i][++j] != 0)
				write(1, &env[i][j], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
	}
}

int	check_argv_ex(char *argv)
{
	if (!(ft_isalpha(argv[0])) || argv[0] == '=')
		return (1);
	while (*argv && *argv != '=')
	{
		if (*argv == '.')
			return (1);
		argv++;
	}
	return (0);
}

int	ft_export(char **argv, t_sup *sup)
{
	int	i;
	int	j;

	i = 0;
	if (!argv[1])
		return (env_sort(sup->env));
	while (argv[++i])
	{
		if (check_argv_ex(argv[i]))
			return (error_nva(argv[0], argv[i]));
		else
		{
			j = env_search_same(argv[i], sup->env);
			if (j >= 0)
			{
				free(sup->env[j]);
				sup->env[j] = ft_strdup(argv[i]);
			}
			else
				one_mas_fr_two(sup, argv[i]);
		}
	}
	return (0);
}
