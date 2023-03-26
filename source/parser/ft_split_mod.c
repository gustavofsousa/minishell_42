/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:29:46 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/26 16:23:55 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check when quotes open and close.
static int	is_quotes(char s, int *fq, char *quote)
{
	if ((s == '"' || s == '\'') && *fq == 0)
	{
		*fq = 1;
		*quote = s;
		return (1);
	}
	else if (*fq == 1 && s == *quote)
	{
		*fq = 0;
		return (1);
	}
	return (0);
}

static size_t	count_words(char const *s, char sep, int *fq)
{
	size_t	i;
	size_t	qtd_word;
	size_t	next;
	char	quote;

	i = 0;
	qtd_word = 0;
	while (s[i])
	{
		is_quotes(s[i], fq, &quote);
		next = i + 1;
		if (s[i] != sep && (s[next] == sep || s[next] == '\0') && *fq != 1)
			qtd_word++;
		i++;
	}
	return (qtd_word);
}

static int	build_line(const char **s, char sep, int *fq)
{
	size_t	word_len;
	char	quote;

	word_len = 0;
	while (**s && (word_len == 0 || **s != sep || *fq == 1))
	{
		is_quotes(**s, fq, &quote);
		if (**s != sep || *fq == 1)
			word_len++;
		(*s)++;
	}
	return (word_len);
}

static char	**split(char **str_splitted, char const *s, char sep, int *fq)
{
	size_t	qtd_words;
	size_t	line;
	int		word_len;

	qtd_words = count_words(s, sep, fq);
	line = 0;
	while (line < qtd_words)
	{
		word_len = build_line(&s, sep, fq);
		str_splitted[line] = ft_substr(s - word_len, 0, word_len);
		s++;
		line++;
	}
	str_splitted[line] = 0;
	return (str_splitted);
}

char	**ft_split_mod(char const *s, char c, int *fq)
{
	char	**str_splitted;
	size_t	qtd_words;

	if (!s)
		return (NULL);
	qtd_words = count_words(s, c, fq);
	if (*fq == 1)
		return (NULL);
	str_splitted = malloc((qtd_words + 1) * sizeof(char *));
	if (!str_splitted)
		return (NULL);
	return (split(str_splitted, s, c, fq));
}
