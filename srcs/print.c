/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/22 17:58:32 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_img(void *mlx_ptr, void *win_ptr,t_scene *scene)
{
	// t_rgb	rgb;
	int		x;
	int		y;
	int		color;
	t_ray	ray;
	// rgb = ft_t_rgb(0120, 0120, 0120);
	// color = ft_rgb(rgb);
	// mlx_string_put(mlx_ptr, win_ptr, 100, 50,  07777777770, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 100, 07777770000, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 150, 01201201200, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 200, color, 		"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 250, 07770000000, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 300, 00007770000, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 350, 00000007770, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 400, 07770007770, 	"Bonne Annee");
	// mlx_string_put(mlx_ptr, win_ptr, 100, 450, 00007777770, 	"Bonne Annee");

	y = -1;
	// for each pixel of the screen
	while (++y < scene->resolution.y)
	{
		x = -1;
		while (++x < scene->resolution.x)
		{
			//Final color = 0;
			color = rgb_to_int(float_to_rgb(x/4, y/8, (x+y)/12));
			//Ray = { starting point, direction };
			ray = new_ray(((t_camera*)(scene->cameras->content))->pos, ((t_camera*)(scene->cameras->content))->orientation);
			//Repeat until reflection factor is 0 or maximum depth is reached;
			{
				//5
				//for each object in the scene
					{
						//determine closest ray object/intersection;
					}
					//if intersection exists
					{
						//for each light in the scene
						{
							//if the light is not in shadow of another object
							{
								//add this light contribution to computed color;
							}
						}
					}
				//Final color = Final color + computed color * previous reflection factor;
				//reflection factor = reflection factor * surface reflection property;
				//increment depth;

				mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			}
		}
	}
}