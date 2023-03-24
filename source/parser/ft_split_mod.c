/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:29:46 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/23 19:21:02 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check when quotes open and close.
static void	is_quotes(char s, size_t *fq, char *quote)
{
	if ((s == '"' || s == '\'') && *fq == 0)
	{
		*fq = 1;
		*quote = s;
	}
	else if (*fq == 1 && s == *quote)
		*fq = 0;
}

static size_t	count_words(char const *s, char sep)
{
	size_t	i;
	size_t	qtd_word;
	size_t	next;
	size_t	fq;
	char	quote;

	i = 0;
	qtd_word = 0;
	fq = 0;
	while (s[i])
	{
		is_quotes(s[i], &fq, &quote);
		next = i + 1;
		if (s[i] != sep && (s[next] == sep || s[next] == '\0') && fq != 1)
			qtd_word++;
		i++;
	}
	return (qtd_word);
}

static char	**split(char	**str_splitted, char const *s, char sep)
{
	size_t	qtd_words;
	size_t	line;
	size_t	word_len;
	size_t	fq;
	char	quote;

	qtd_words = count_words(s, sep);
	line = 0;
	fq = 0;
	while (line < qtd_words)
	{
		word_len = 0;
		while (*s && (word_len == 0 || *s != sep || fq == 1))
		{
			is_quotes(*s, &fq, &quote);
			if (*s != sep || fq == 1)
				word_len++;
			s++;
		}
		str_splitted[line] = ft_substr(s - word_len, 0, word_len);
		line++;
	}
	str_splitted[line] = 0;
	return (str_splitted);
}

char	**ft_split_mod(char const *s, char c)
{
	char	**str_splitted;
	size_t	qtd_words;

	if (!s)
		return (NULL);
	qtd_words = count_words(s, c);
	str_splitted = malloc((qtd_words + 1) * sizeof(char *));
	if (!str_splitted)
		return (NULL);
	return (split(str_splitted, s, c));
}
