/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:56:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/06 16:05:25 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_width(int nb, int width)
{
	char	**res;
	int		diff;
	int		i;

	if (!(res = malloc(sizeof(*res))))
		return (NULL);
	if (!(*res = malloc((width + 1) * sizeof(char))))
		return (NULL);
	diff = width - ft_nbrlen(nb);
	if (diff > 0)
	{
		i = 0;
		while (i < diff)
			*res[i++] = '0';
	}
	ft_memcpy(*res + diff, ft_itoa(nb), ft_nbrlen(nb));
	return (*res);
}