/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:04:54 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/07 11:28:08 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c1;

	c1 = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c1)
			return ((char*)s + i);
		i++;
	}
	if (s[i] == c1)
		return ((char*)s + i);
	return (NULL);
}
