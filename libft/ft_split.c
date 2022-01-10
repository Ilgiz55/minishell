/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchau <rchau@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:32:39 by rchau             #+#    #+#             */
/*   Updated: 2022/01/10 15:36:33 by rchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] && s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			len++;
		}
	}
	return (len);
}

static size_t	wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*leak(char **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static void	put_words(char **tab, size_t word, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	n;
	size_t	len;

	i = 0;
	n = 0;
	while (n < word)
	{
		while (s[i] && s[i] == c)
			i++;
		len = wordlen(&s[i], c);
		tab[n] = (char *)malloc(sizeof(char) * (len + 1));
		if (!tab[n])
			leak(tab, n);
		j = 0;
		while (s[i] && j < len)
			tab[n][j++] = s[i++];
		tab[n][j] = '\0';
		n++;
	}
	tab[n] = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	char	**tab;

	if (!s)
		return (NULL);
	word = words(s, c);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	put_words(tab, word, s, c);
	return (tab);
}
