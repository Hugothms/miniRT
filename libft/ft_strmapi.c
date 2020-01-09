/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:29:55 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/06 16:29:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (!(new = malloc((ft_strlen(s) + 1) * sizeof(char))))
		return (NULL);
	while (s[i])
	{
		new[i] = (f)(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
