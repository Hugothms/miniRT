/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/08 11:40:47 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <stdio.h>

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

void 	ft_print(void *mlx_ptr, void *win_ptr)
{
	t_rgb	rgb;
	int		x;
	int		y;
	int		color;

	rgb = ft_t_rgb(0120, 0120, 0120);
	color = ft_rgb(rgb);

	mlx_string_put(mlx_ptr,win_ptr, 100, 150, 01201201200,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 200, color,			"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 250, 07770000000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 300, 00007770000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 350, 00000007770,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 400, 07770007770,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 450, 00007777770,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 500, 07777770000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 550, 07777777770,		"Bonne Annee" );
}

int 	main(int argc, char const *argv[])
{
	void	*mlx_ptr;
	void	*win_ptr;

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
