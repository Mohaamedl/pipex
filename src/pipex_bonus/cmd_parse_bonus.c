/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:45:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/13 19:45:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	count_words(char *str)
{
	int	count;
	int	in_word;
	int	in_quotes;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	while (*str)
	{
		if (is_quote(*str) && !in_quotes)
			in_quotes = *str;
		else if (in_quotes && *str == in_quotes)
			in_quotes = 0;
		else if (*str == ' ' && !in_quotes && in_word)
			in_word = 0;
		else if (*str != ' ' && !in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static int	get_word_len(char *str)
{
	int	len;
	int	in_quotes;

	len = 0;
	in_quotes = 0;
	while (str[len])
	{
		if (is_quote(str[len]) && !in_quotes)
			in_quotes = str[len];
		else if (in_quotes && str[len] == in_quotes)
			in_quotes = 0;
		else if (str[len] == ' ' && !in_quotes)
			break ;
		len++;
	}
	return (len);
}

static char	*extract_word(char *str, int len)
{
	char	*word;
	int		i;
	int		j;
	int		in_quotes;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	while (i < len)
	{
		if (is_quote(str[i]) && !in_quotes)
			in_quotes = str[i];
		else if (in_quotes && str[i] == in_quotes)
			in_quotes = 0;
		else
			word[j++] = str[i];
		i++;
	}
	word[j] = '\0';
	return (word);
}

char	**parse_command(char *cmd)
{
	char	**args;
	int		word_count;
	int		i;
	int		word_len;

	word_count = count_words(cmd);
	if (word_count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (word_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*cmd && i < word_count)
	{
		while (*cmd == ' ')
			cmd++;
		word_len = get_word_len(cmd);
		args[i] = extract_word(cmd, word_len);
		if (!args[i])
			return (NULL);
		cmd += word_len;
		i++;
	}
	args[i] = NULL;
	return (args);
}
