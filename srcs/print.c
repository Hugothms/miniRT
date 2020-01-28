/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/28 15:06:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray		trace_ray(t_list* cameras, t_couple resolution, int i, int j)
{
	t_vect	vect_dir;

	//Ray = { starting point, direction };
	vect_dir = set_vect_dir_cam(((t_camera*)cameras->content), resolution, i, j);
	//printf("position:\t(% .3f,\t% .3f,\t% .3f)\n",\
											((t_camera*)cameras->content)->pos.x,\
											((t_camera*)cameras->content)->pos.y,\
											((t_camera*)cameras->content)->pos.z);
	//printf("direction:%s\t(% .3f,\t% .3f,\t % .3f)\n\n",\
											i  == resolution.h / 2 \
											&& j == resolution.w / 2 ? "\tmiddle\n\n" : "",\
											vect_dir.x,\
											vect_dir.y,\
											vect_dir.z);
	return(new_ray(((t_camera*)(cameras))->pos, vect_dir));
}

void	print_img(void *mlx_ptr, void *win_ptr,t_scene *scene)
{
	int		j;
	int		i;
	int		color;
	t_ray	ray;

	i = -1;
	while (++i < scene->resolution.h)
	{
		j = -1;
		while (++j < scene->resolution.w)
		{
			//Final color = 0;
			color = rgb_to_int(float_to_rgb(0, 0, 0));
			ray = trace_ray(scene->cameras, scene->resolution, i, j);
			//Repeat until reflection factor is 0 or maximum depth is reached;
			int	depth = 1;
			while(depth--)
			{
				//5
				//for each object in the scene
					{
						//determine closest ray object/intersection;
					}
					//if intersection exists
					t_sphere shpere =  *(t_sphere*)(scene->spheres->content);
					if (intersect(ray, shpere))
					{
						//for each light in the scene
						{
							//if the light is not in shadow of another object
							{
								//add this light contribution to computed color;
							}
						}
						color = rgb_to_int(float_to_rgb(255, 0, 0));
					}
				//Final color = Final color + computed color * previous reflection factor;
				//reflection factor = reflection factor * surface reflection property;
				mlx_pixel_put(mlx_ptr, win_ptr, j, i, color);
			}
		}
	}
}
