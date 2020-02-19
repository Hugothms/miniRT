/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:20:18 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/19 20:04:26 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_rgb	*int_to_rgb(int r, int g, int b)
{
	t_rgb	*rgb;

	if(!(rgb = malloc(sizeof(*rgb))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

t_rgb	char_to_rgb(char *r, char *g, char *b)
{
	t_rgb	rgb;

	rgb.r = ft_atoi(r);
	rgb.g = ft_atoi(g);
	rgb.b = ft_atoi(b);
	return (rgb);
}

int		rgb_to_int(t_rgb rgb)
{
	return(rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_rgb	*mult_rgb(t_rgb rgb, t_rgb mult)
{
	return (int_to_rgb(rgb.r * (mult.r / 255.), rgb.g * (mult.g / 255.), rgb.b * (mult.b / 255.)));
}

int		get_t(int color)
{
	return (color & 0xFF);
}

int		get_r(int color)
{
	return (color & 0xFF00);
}

int		get_g(int color)
{
	return (color & 0xFF0000);
}

int		get_b(int color)
{
	return (color & 0xFF000000);
}
