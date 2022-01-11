/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:02:09 by laubrey           #+#    #+#             */
/*   Updated: 2022/01/11 20:02:21 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_checker(char *argv)
{
	int	i;

	g_status = 0;
	i = 0;
	if (argv[0] != '_' && !ft_isalpha(argv[0]))
	{
		g_status = error_nva("unset", argv);
		return (g_status);
	}
	while (argv[i])
	{
		if (argv[i] != '_' && argv[i] != '=' && argv[i] != '+'
			&& !ft_isalpha(argv[i]) && !ft_isdigit(argv[i]))
			g_status = error_nva("unset", argv);
		if (argv[i] == '+' && argv[i + 1] != '=')
			g_status = error_nva("unset", argv);
		i++;
	}
	return (g_status);
}

void	uns_rewrite(char **env, int n)
{
	char	*sup;

	while (env[n])
	{
		sup = env[n + 1];
		free(env[n]);
		if (sup != NULL)
		{
			env[n] = ft_strdup(sup);
			n++;
		}
		else
			env[n] = NULL;
	}
}

int	ft_unset(char **argv, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (!argv[1] || *(argv[1]) == '\0')
		return (0);
	while (argv[++i])
	{
		if (!unset_checker(argv[i]))
		{
			j = env_search_same(argv[i], env);
			if (j >= 0)
				uns_rewrite(env, j);
			g_status = 0;
		}
		i++;
	}
	return (g_status);
}
