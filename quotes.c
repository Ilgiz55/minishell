/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:36 by rchau             #+#    #+#             */
/*   Updated: 2022/01/02 21:07:10 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_double_quotes(char **s, int *j, char **env)
{
	int		i;
	char	**tmp;
	char	*str;

	i = *j + 1;
	tmp = (char **)malloc(sizeof(char *) * 4);
	ft_check_dollar_in_quotes(s, &i, env);
	str = *s;
	tmp[0] = ft_substr(str, 0, (*j)++);
	tmp[1] = ft_substr(str, *j, i - *j);
	tmp[2] = ft_strdup(str + i + 1);
	tmp[3] = ft_strjoin(tmp[0], tmp[1]);
	str = ft_strjoin(tmp[3], tmp[2]);
	ft_free_tmp(tmp, 4);
	free(*s);
	*j = i - 2;
	*s = str;
}

void	ft_check_dollar_in_quotes(char **s, int *i, char **env)
{
	char	*str;
	int		j;

	j = *i;
	str = *s;
	while (str[*i] != '\"')
	{
		if (str[*i] == '$')
			ft_dollar(s, i, env);
		(*i)++;
	}
	str = *s;
	while (str[j] != '\"')
		j++;
	*i = j;
}

void	ft_quotes(char **s, int *k)
{
	int		j;
	int		i;
	char	**tmp;
	char	*str;

	j = *k;
	i = *k;
	tmp = (char **)malloc(sizeof(char *) * 4);
	str = *s;
	while (str[++i])
		if (str[i] == '\'')
			break ;
	tmp[0] = ft_substr(str, 0, j++);
	tmp[1] = ft_substr(str, j, i - j);
	tmp[2] = ft_strdup(str + i + 1);
	tmp[3] = ft_strjoin(tmp[0], tmp[1]);
	str = ft_strjoin(tmp[3], tmp[2]);
	ft_free_tmp(tmp, 4);
	free(*s);
	*k = i - 2;
	*s = str;
}

char	*ft_open_quotes(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			ft_quotes(&str, &i);
		if (str[i] == '\"')
			ft_double_quotes(&str, &i, env);
		if (str[i] == '$')
			ft_dollar(&str, &i, env);
	}
	return (str);
}

int	ft_check_open_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			while (str[++i] != '\"')
				if (str[i] == '\0')
					return (1);
		if (str[i] == '\'')
			while (str[++i] != '\'')
				if (str[i] == '\0')
					return (1);
		i++;
	}
	return (0);
}
