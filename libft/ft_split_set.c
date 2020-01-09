/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 08:16:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 15:05:29 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		in_charset(char c, char const *charset)
{
	int	i_charset;

	i_charset = 0;
	while (charset[i_charset])
	{
		if (c == charset[i_charset++])
			return (1);
	}
	return (0);
}

int		*count_lengths(int *words_len, const char *str, char *charset)
{
	int	i_length;
	int	i_str;

	i_length = 0;
	i_str = 0;
	while (str[i_str])
	{
		while (str[i_str])
		{
			if (!in_charset(str[i_str], charset))
				break ;
			i_str++;
		}
		while (str[i_str])
		{
			if (in_charset(str[i_str], charset))
				break ;
			i_str++;
			words_len[i_length]++;
		}
		i_length++;
	}
	return (words_len);
}

int		count_words(const char *str, char *charset)
{
	int	count;
	int	i_str;

	count = 0;
	i_str = 0;
	while (str[i_str])
	{
		while (str[i_str])
		{
			if (!in_charset(str[i_str], charset))
			{
				count++;
				break ;
			}
			i_str++;
		}
		while (str[i_str])
		{
			if (in_charset(str[i_str++], charset))
				break ;
		}
	}
	return (count);
}

int		fill_tab(char ***tab, int *words_len, const char *str, char *charset)
{
	int		d1;
	int		d2;
	int		i_str;
	int		words_count;

	d1 = 0;
	i_str = 0;
	words_count = count_words(str, charset);
	while (d1 < words_count && str[i_str])
	{
		if (!((*tab)[d1] = malloc((words_len[d1] + 1) * sizeof(char))))
			return (0);
		while (in_charset(str[i_str], charset))
			i_str++;
		d2 = 0;
		while (str[i_str] && !in_charset(str[i_str], charset))
			(*tab)[d1][d2++] = str[i_str++];
		(*tab)[d1][d2++] = '\0';
		d1++;
	}
	(d1 != 0) ? (*tab)[d1 - 1][d2] = '\0' : 0;
	(*tab)[d1] = 0;
	return (1);
}

/*
** split str into a char** each time there is a char from charset
** @param str		"sentence" that will be splited
** @param charset	set of "delimiters" that will delimits the "words"
** @return			a char** of "words"
*/

char	**ft_split_set(const char *str, char *charset)
{
	char	**tab;
	int		words_count;
	int		words_len[count_words(str, charset)];
	int		allgood;
	int		i;

	if (!str)
		return (0);
	words_count = count_words(str, charset);
	if (!(tab = malloc((words_count + 1) * sizeof(char*))))
		return (0);
	i = 0;
	while (i < words_count)
		words_len[i++] = 0;
	count_lengths(words_len, str, charset);
	allgood = fill_tab(&tab, words_len, str, charset);
	if (allgood)
		return (tab);
	return (0);
}
