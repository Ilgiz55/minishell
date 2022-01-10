/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:12:29 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 14:13:28 by rchau            ###   ########.fr       */
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
