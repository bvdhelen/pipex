/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:33:06 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/29 10:33:06 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**free_memory(char **result, int count)
{
	while (count >= 0)
	{
		free(result[count]);
		count--;
	}
	free(result);
	return (NULL);
}

static int	count_shell_words(const char *s)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else
		{
			while (s[i] && !ft_isspace(s[i]))
				i++;
		}
	}
	return (count);
}

static char	*extract_shell_word(const char *s, int start)
{
	int		i;
	int		len;
	char	quote;
	char	*word;
	char	*trimmed;

	i = start;
	len = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	start = i;
	if (s[i] == '\'' || s[i] == '"')
	{
		quote = s[i];
		i++;
		start = i;
		while (s[i] && s[i] != quote)
		{
			len++;
			i++;
		}
	}
	else
	{
		while (s[i] && !ft_isspace(s[i]))
		{
			len++;
			i++;
		}
	}
	word = ft_substr(s, start, len);
	if (!word)
		return (NULL);
	trimmed = ft_strtrim(word, "'\"");
	free(word);
	return (trimmed);
}

static int	skip_word(const char *s, int i)
{
	char	quote;

	if (s[i] == '\'' || s[i] == '"')
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] == quote)
			i++;
	}
	else
	{
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (i);
}

char	**ft_split_with_quotes(const char *s)
{
	char	**result;
	char	*word;
	int		word_count;
	int		i;
	int		j;

	word_count = count_shell_words(s);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		word = extract_shell_word(s, i);
		if (!word)
			return (free_memory(result, j - 1));
		result[j] = word;
		j++;
		i = skip_word(s, i);
	}
	result[j] = NULL;
	return (result);
}
