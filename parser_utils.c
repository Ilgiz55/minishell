/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:05:31 by rchau             #+#    #+#             */
/*   Updated: 2022/01/05 11:11:18 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tmp(char **tmp, int n)
{
	while (n--)
		free(tmp[n]);
}

t_msh	*ft_mshnew(void)
{
	t_msh	*element;

	element = (t_msh *)malloc(sizeof(*element));
	element->argc = 0;
	element->fdin = 0;
	element->fdout = 1;
	element->next = NULL;
	element->prev = NULL;
	element->outfile = NULL;
	element->infile = NULL;
	return (element);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_skip_space(char *str, int i)
{
	while (str[i] == ' ' || str[i] =='\t')
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
