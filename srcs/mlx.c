/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:43:06 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/03 10:47:53 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void        ft_put_pixel(char *data, t_couple pixel, int color, int win_width)
{
    int (*tab)[win_width][1]; // prepare the cast

    tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
    *tab[pixel.w][pixel.h] = color; // set the pixel at the coord x,y with the color value
}