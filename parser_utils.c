/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:31 by rchau             #+#    #+#             */
/*   Updated: 2022/01/11 17:56:58 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tmp(char **tmp, int n)
{
	while (n--)
		free(tmp[n]);
	free(tmp);
}

t_msh	*ft_mshnew(void)
{
	t_msh	*element;

	element = (t_msh *)malloc(sizeof(t_msh));
	if (!element)
		return (NULL);
	element->argc = 0;
	element->argv = NULL;
	element->fdin = 0;
	element->fdout = 1;
	element->pid = 0;
	element->write_mode = 0;
	element->next = NULL;
	element->prev = NULL;
	element->outfile = NULL;
	element->infile = NULL;
	return (element);
}

int	ft_error(char *str, int status)
{
	char	*s;

	s = ft_strjoin("minishell: ", str);
	printf("%s\n", s);
	free(s);
	g_status = status;
	return (1);
}

int	ft_skip_space(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

char	*ft_get_stop_word(char *str, int *j)
{
	int		i;
	char	*stop_word;

	i = *j;
	while (str[i] && str[i] != '|' && str[i] != '>' \
		&& str[i] != '<' && str[i] != ' ')
		i++;
	stop_word = ft_substr(str, *j, i - *j);
	*j = i;
	return (stop_word);
}
