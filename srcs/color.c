/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:20:18 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/25 20:35:42 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_rgb	*int_to_rgb(const int r, const int g, const int b)
{
	t_rgb	*rgb;

	if(!(rgb = malloc(sizeof(*rgb))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

t_rgb	char_to_rgb(const char *r, const char *g, const char *b)
{
	t_rgb	rgb;

	rgb.r = ft_atoi(r);
	rgb.g = ft_atoi(g);
	rgb.b = ft_atoi(b);
	return (rgb);
}

int	rgb_to_int(const t_rgb rgb)
{
	return(rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_rgb	*mult_rgb_rgb(const t_rgb rgb, const t_rgb mult)
{
	return (int_to_rgb(rgb.r * (mult.r / 255.), rgb.g * (mult.g / 255.), rgb.b * (mult.b / 255.)));
}

t_rgb	*mult_rgb_double(const t_rgb rgb, const double mult)
{
	return (int_to_rgb(rgb.r * mult, rgb.g * mult, rgb.b * mult));
}

t_rgb	*add_rgb_rgb(const t_rgb rgb, const t_rgb add)
{
	return (int_to_rgb(rgb.r + add.r, rgb.g + add.g, rgb.b + add.b));
}

void	min_rgb(t_rgb *color)
{
	color->r = ft_min_int(color->r, 255);
	color->g = ft_min_int(color->g, 255);
	color->b = ft_min_int(color->b, 255);
}

t_rgb	get_color(const char *type, const void *object)
{
	if (!ft_strcmp(type, "sp"))
		return((t_sphere*)object)->color;
	if (!ft_strcmp(type, "pl"))
		return((t_plane*)object)->color;
	if (!ft_strcmp(type, "cy"))
		return((t_cylinder*)object)->color;
	if (!ft_strcmp(type, "tr"))
		return((t_triangle*)object)->color;
	// if (!ft_strcmp(type, "sq"))
		return((t_square*)object)->color;
}
