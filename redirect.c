/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:07:21 by rchau             #+#    #+#             */
/*   Updated: 2022/01/09 15:38:40 by rchau            ###   ########.fr       */
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
			msh->write_mode = 2;
		else
			msh->write_mode = 1;
		error = ft_redirect_output(str, &i, msh);
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
	int		fd;
	char	*s;

	i = *j;
	i = ft_skip_space(str, i);
	if (str[i] == '>' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
		return (ft_error("syntax error", 258));
	file_name = ft_get_file_name(str, &i);
	fd = open(file_name, O_RDONLY, 0644);
	if (fd < 0)
	{
		s = ft_strjoin(file_name, ": No such file or directory");
		ft_error(s, 1);
		free(s);
		free(file_name);
		return (1);
	}
	close(fd);
	msh->infile = ft_strdup(file_name);
	free(file_name);
	*j = i;
	return (0);
}

int	ft_redirect_output(char *str, int *j, t_msh *msh)
{
	char	*file_name;
	int		i;
	int		fd;

	if (str[*j] == '>')
		(*j)++;
	i = *j;
	i = ft_skip_space(str, i);
	if (str[i] == '<' || str[i] == ';' || str[i] == '|' || str[i] == '\0')
		return (ft_error("syntax error", 258));
	file_name = ft_get_file_name(str, &i);
	fd = open(file_name, O_WRONLY | O_CREAT, 0644);
	close(fd);
	if (msh->outfile)
		free(msh->outfile);
	msh->outfile = ft_strdup(file_name);
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
		return (ft_error("syntax error", 258));
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
