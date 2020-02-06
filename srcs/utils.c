/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:24:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/06 16:05:32 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*screenshot_datetime()
{
	char		*res[35];
	time_t		t;
	struct tm	tm;

	t = time(NULL);
	tm = *localtime(&t);
	*res = ft_strdup("Screenshot YYYY-MM-DD hh:mm:ss.bmp");
	ft_memcpy(*res + 11, ft_itoa_width(tm.tm_year + 1900, 4), 4);
	ft_memcpy(*res + 16, ft_itoa_width(tm.tm_mon + 1, 2), 2);
	ft_memcpy(*res + 19, ft_itoa_width(tm.tm_mday, 2), 2);
	ft_memcpy(*res + 22, ft_itoa_width(tm.tm_hour, 2), 2);
	ft_memcpy(*res + 25, ft_itoa_width(tm.tm_min, 2), 2);
	ft_memcpy(*res + 28, ft_itoa_width(tm.tm_sec, 2), 2);
	return (*res);
}
