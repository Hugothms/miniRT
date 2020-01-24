/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/24 10:54:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_img(void *mlx_ptr, void *win_ptr,t_scene *scene)
{
	// t_rgb	rgb;
	int		j;
	int		i;
	int		color;
	t_vect	vect_dir;
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

	i = -1;
	// for each pixel of the screen
	while (++i < scene->resolution.h)
	{
		j = -1;
		while (++j < scene->resolution.w)
		{
			//Final color = 0;
			color = rgb_to_int(float_to_rgb(j/4, i/8, (j+i)/12));
			//Ray = { starting point, direction };
			vect_dir = ((t_camera*)scene->cameras->next->content)->orientation;
			vect_dir.x += j - (scene->resolution.w - 1) / 2.;
			vect_dir.y += i - (scene->resolution.h - 1) / 2.;
			vect_dir.z += scene->resolution.w / (2 * tan((((t_camera*)scene->cameras->next->content)->fov / 2) * (M_PI / 180)));
			printf("position:\t(%.1f,\t%.1f,\t%.1f)\ndirection:%s\t(%.1f, \t%.1f, \t %.1f)\n\n",
													((t_camera*)scene->cameras->next->content)->pos.x,
													((t_camera*)scene->cameras->next->content)->pos.y,
													((t_camera*)scene->cameras->next->content)->pos.z,
													i  == scene->resolution.h /2 && j == scene->resolution.w /2? "middle\n\n" : "",
													vect_dir.x,
													vect_dir.y,
													vect_dir.z);
			ray = new_ray(((t_camera*)(scene->cameras->next))->pos, vect_dir);
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

				mlx_pixel_put(mlx_ptr, win_ptr, j, i, color);
			}
		}
	}
}