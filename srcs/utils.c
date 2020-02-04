/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:24:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/04 10:26:23 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char		*str_width(int nb, int width)
{
	char	**res;
	int		diff;
	int		i;

	if (!(res = malloc(sizeof(*res))))
		return (NULL);
	if(!(*res = malloc((width + 1) * sizeof(char))))
		return (NULL);
	diff = width - nbrlen(nb);
	if (diff > 0)
	{
		i = 0;
		while (i < diff)
			*res[i++] = '0';
	}
	ft_memcpy(*res + diff, ft_itoa(nb), nbrlen(nb));
	return (*res);
}

char	*screenshot_datetime()
{
	char	*res[35];

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	*res = ft_strdup("Screenshot 0000-00-00 00:00:00.bmp");
	ft_memcpy(*res + 11, str_width(tm.tm_year + 1900, 4), 4);
	ft_memcpy(*res + 16, str_width(tm.tm_mon + 1, 2), 2);
	ft_memcpy(*res + 19, str_width(tm.tm_mday, 2), 2);
	ft_memcpy(*res + 22, str_width(tm.tm_hour, 2), 2);
	ft_memcpy(*res + 25, str_width(tm.tm_min, 2), 2);
	ft_memcpy(*res + 28, str_width(tm.tm_sec, 2), 2);
	return (*res);
}
