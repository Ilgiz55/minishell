/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:07:21 by rchau             #+#    #+#             */
/*   Updated: 2022/01/02 21:51:54 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect(t_msh *msh, char *str, int *j)
{
	int	i;
	int	error;

	i = *j;
	error = 0;
	if (str[i] == '>')
	{
		if (str[++i] == '>')
			error = ft_redirect_output(str, &i, msh, 2);
		else
			error = ft_redirect_output(str, &i, msh, 1);
	}
	else
	{
		if (str[++i] == '<')
			error = ft_stop_word(str, &i, msh);
		else
			error = ft_redirect_input(str, &i, msh);
	}
	*j = i;
	return (error);
}

int	ft_redirect_input(char *str, int *j, t_msh *msh)
{
	char	*file_name;
	int		i;

	i = *j;
	i = ft_skip_space(str, i);
	if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
		return (ft_error("syntax error"));
	file_name = ft_get_file_name(str, &i);
	if (msh->fdin > 0)
		close(msh->fdin);
	msh->fdin = open(file_name, O_RDONLY, 0644);
	if (msh->fdin < 0)
	{
		printf("%s: No such file or directory\n", file_name);
		free(file_name);
		return (1);
	}
	free(file_name);
	*j = i;
	return (0);
}

int	ft_redirect_output(char *str, int *j, t_msh *msh, int flag)
{
	char	*file_name;
	int		i;

	if (str[*j] == '>')
		(*j)++;
	i = *j;
	i = ft_skip_space(str, i);
	if (str[i] == '<' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
		return (ft_error("syntax error"));
	file_name = ft_get_file_name(str, &i);
	if (msh->fdout > 2)
		close(msh->fdout);
	if (flag == 2)
		msh->fdout = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		msh->fdout = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file_name);
	*j = i;
	return (0);
}

int	ft_stop_word(char *str, int *i, t_msh *msh)
{
	char	*stop_word;
	char	*new_word;

	*i = ft_skip_space(str, ++(*i));
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == ';' || \
		str[*i] == '|' || str[*i] == '\0')
		return (ft_error("syntax error"));
	stop_word = ft_get_stop_word(str, i);
	new_word = readline(">");
	while (1)
	{
		if (!ft_strncmp(stop_word, new_word, \
			ft_strlen(stop_word) + ft_strlen(new_word)))
			break ;
		free(new_word);
		new_word = readline(">");
	}
	free(new_word);
	free(stop_word);
	return (0);
}

char	*ft_get_file_name(char *str, int *i)
{
	int		j;
	char	*file_name;

	j = *i;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '|'))
		*i += 1;
	file_name = ft_substr(str, j, *i - j);
	return (file_name);
}
