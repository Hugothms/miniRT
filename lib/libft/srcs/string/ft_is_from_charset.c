/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_from_charset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:59:06 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:08:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** check if str is only made of char in charset
** @param str	string that will be checked
** @param set	set of chars
** @return		1 if there are only chars from charset in str, 0 otherwise
*/

int		ft_is_from_charset(const char *str, const char *charset)
{
	int	i;
	int	j;
	int	ok;

	i = 0;
	while (str[i])
	{
		ok = 0;
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j++])
				ok = 1;
		}
		if (!ok)
			return (0);
		i++;
	}
	return (1);
}
