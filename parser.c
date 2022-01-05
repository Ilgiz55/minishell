/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 20:50:40 by rchau             #+#    #+#             */
/*   Updated: 2022/01/05 11:12:00 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_argc(char *str, int i)
{
	int	n;

	n = 0;
	while (str[i] && str[i] != '|')
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && (str[i] != ' '))
		{
			if (str[i] == '\"')
				while (str[++i] != '\"')
					;
			if (str[i] == '\'')
				while (str[++i] != '\'')
					;
			i++;
		}
		n++;
	}
	return (n);
}

int	ft_arg_len(char *str, int i)
{
	int	j;

	j = i;
	while (str[i] && (str[i] != ' ' && str[i] != '|' && \
		str[i] != '>' && str[i] != '<'))
	{
		if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		i++;
	}
	return (i - j);
}

int	ft_new_command(t_msh **msh_p, char *str, int *k)
{
	int		i;
	t_msh	*msh;

	if (str[*k] != '|')
		return (0);
	i = *k;
	msh = *msh_p;
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0' && str[i] != '|' && str[i] != '>' && str[i] != '<')
		return (1);
	msh->next = ft_mshnew();
	msh->next->prev = msh;
	msh = msh->next;
	msh->argv = (char **)malloc(sizeof(char *) * (ft_argc(str, i) + 1));
	*k = i;
	*msh_p = msh;
	return (0);
}

int	ft_check_start(char *str, int *j)
{
	int	i;

	if (*str == '\0')
		return (1);
	if (ft_check_open_quotes(str))
		return (ft_error("syntax error: open quotes"));
	i = 0;
	i = ft_skip_space(str, i);
	if (str[i] == '|' || str[i] == ';')
		return (ft_error("syntax error"));
	*j = i;
	return (0);
}

int	ft_parser(t_msh *msh, char *str, char **env)
{
	int		i;
	int		n;

	if (ft_check_start(str, &i))
		return (1);
	msh->argv = (char **)malloc(sizeof(char *) * (ft_argc(str, i) + 1));
	msh->argv[msh->argc] = NULL;
	while (str[i])
	{
		n = ft_arg_len(str, i);
		if (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<')
			msh->argv[msh->argc] = ft_open_quotes(ft_substr(str, i, n), env);
		if (msh->argv[msh->argc])
			msh->argc++;
		msh->argv[msh->argc] = NULL;
		i = ft_skip_space(str, i + n);
		if (str[i] == '>' || str[i] == '<')
			if (ft_redirect(msh, str, &i))
				return (1);
		i = ft_skip_space(str, i);
		if (ft_new_command(&msh, str, &i))
			return (ft_error("pipe error"));
	}
	return (0);
}
