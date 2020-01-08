/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/08 10:55:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <stdio.h>

void ft_print(void *mlx_ptr, void *win_ptr)
{
	t_rgb	rgb;
	int x;
	int y;
	int color;
	int cible;

	x = 20;
	y = 30;

	rgb.r = 0;
	rgb.g = 012;
	rgb.b = 0;
	mlx_pixel_put(mlx_ptr,win_ptr, x, y, 255 );

	color = 0;
 	color += 2097152 * rgb.r;
 	color += 4096 * rgb.g;
 	color += 8 * rgb.b;
	cible = 00000120000;
	printf("color:\t%d\ncible:\t%d\ncible2:\t%d\n\n",color, cible, 0000120000);

	 mlx_string_put(mlx_ptr,win_ptr, x + 100, y + 100, 02552552550,			"Bonne Annee" );
 	mlx_string_put(mlx_ptr,win_ptr, x + 100, y + 150, color,		"Bonne Annee" );
 	mlx_string_put(mlx_ptr,win_ptr, x + 100, y + 200, cible, 		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, x + 100, y + 250, 02550000000, 		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, x + 100, y + 300, 00010000000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, x + 100, y + 350, 02552552550,		"Bonne Annee" );
}

int main(int argc, char const *argv[])
{
	void *mlx_ptr;
	void *win_ptr;

	if(!(mlx_ptr = mlx_init()))
		return (-1);
	if(!(win_ptr = mlx_new_window(mlx_ptr, 500, 1000, "title window")))
		return (-1);
	ft_print(mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
	mlx_clear_window (mlx_ptr, win_ptr );
	mlx_destroy_window (mlx_ptr, win_ptr );
	return (0);
}
