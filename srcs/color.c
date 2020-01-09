/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:20:18 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 12:21:19 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_rgb	ft_t_rgb(int r, int g, int b)
{
	t_rgb	rgb;

 	rgb.r =  r;
 	rgb.g =  g;
 	rgb.b =  b;
	return (rgb);
}

int		ft_rgb(t_rgb rgb)
{
	int	color;

	color = 0;
 	color += 2097152 * rgb.r;
 	color += 4096 * rgb.g;
 	color += 8 * rgb.b;
	return (color);
}
