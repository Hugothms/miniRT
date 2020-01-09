/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:29:42 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 12:26:39 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(new = malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
	ft_memmove(new, s1, lens1);
	ft_memmove(new + lens1, s2, lens2);
	new[lens1 + lens2] = '\0';
	return (new);
}
