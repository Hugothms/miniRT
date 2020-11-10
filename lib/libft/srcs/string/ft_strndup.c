/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:04:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:08:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strndup(char const *src, int size)
{
	int		len;
	char	*cpy;

	len = ft_min_int(ft_strlen(src), size);
	if (!(cpy = malloc((len + 1) * sizeof(char))))
		return (0);
	ft_memcpy(cpy, src, len);
	cpy[len] = '\0';
	return (cpy);
}
