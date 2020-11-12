/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:24:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/12 13:04:58 by hthomas          ###   ########.fr       */
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

int		solve_quadratic(const t_vect point, double *x0, double *x1)
{
	double	discr;
	double	q;

	discr = point.y * point.y - 4 * point.x * point.z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*x0 = -0.5 * point.y / point.x;
		*x1 = -0.5 * point.y / point.x;
	}
	else
	{
		q = (point.y > 0) ? -0.5 * (point.y + sqrt(discr)) : -0.5 * (point.y - sqrt(discr));
		*x0 = q / point.x;
		*x1 = point.z / q;
	}
	if (*x0 > *x1)
		ft_swap(x0, x1);
	return (1);
}

int     ft_tab_size(char **tab)
{
    int i;

    if (!tab)
        return (0);
    i = 0;
    while (tab[i])
        i++;
    return (i);
}