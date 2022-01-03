/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:40 by rchau             #+#    #+#             */
/*   Updated: 2022/01/02 21:06:51 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char **env, char *key)
{
	int		i;
	int		j;
	char	*answer;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(env[i])))
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			answer = ft_substr(env[i], 0, j);
			if (ft_strncmp(key, answer, ft_strlen(key)) == 0)
			{
				free(answer);
				return (ft_substr(env[i], j + 1, ft_strlen(env[i]) - j));
			}
			free(answer);
		}
	}
	return (ft_strdup(""));
}

void	ft_dollar(char **s, int *j, char **env)
{
	int		i;
	char	**tmp;
	char	*str;

	i = *j;
	str = *s;
	tmp = (char **)malloc(sizeof(char *) * 5);
	while (str[++i])
		if (str[i] != '_' && !ft_isalnum(str[i]))
			break ;
	if (i == ++(*j))
		return ;
	tmp[0] = ft_substr(str, *j, i - *j);
	tmp[1] = ft_get_env(env, tmp[0]);
	tmp[2] = ft_substr(str, 0, *j - 1);
	tmp[3] = ft_strdup(str + i);
	tmp[4] = ft_strjoin(tmp[2], tmp[1]);
	str = ft_strjoin(tmp[4], tmp[3]);
	*j = i - 1;
	ft_free_tmp(tmp, 5);
	free(*s);
	*s = str;
}