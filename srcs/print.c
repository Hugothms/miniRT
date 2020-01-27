/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/27 18:14:09 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_img(void *mlx_ptr, void *win_ptr,t_scene *scene)
{
	int		j;
	int		i;
	int		color;
	t_vect	vect_dir;
	t_ray	ray;

	i = -1;
	while (++i < scene->resolution.h)
	{
		j = -1;
		while (++j < scene->resolution.w)
		{
			//Final color = 0;
			color = rgb_to_int(float_to_rgb(0, 0, 0));
			//Ray = { starting point, direction };
			vect_dir = set_vect_dir_cam(((t_camera*)scene->cameras->next->content) , scene->resolution, i, j);
			//printf("position:\t(% .3f,\t% .3f,\t% .3f)\n",\
													((t_camera*)scene->cameras->next->content)->pos.x,\
													((t_camera*)scene->cameras->next->content)->pos.y,\
													((t_camera*)scene->cameras->next->content)->pos.z);
			//printf("direction:%s\t(% .3f,\t% .3f,\t % .3f)\n\n",\
													i  == scene->resolution.h / 2 \
													&& j == scene->resolution.w / 2 ? "\tmiddle\n\n" : "",\
													vect_dir.x,\
													vect_dir.y,\
													vect_dir.z);
			ray = new_ray(((t_camera*)(scene->cameras->next))->pos, vect_dir);
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
					if (intersect(ray, *(t_sphere*)(scene->spheres->content)))
					{
						//for each light in the scene
						{
							//if the light is not in shadow of another object
							{
								//add this light contribution to computed color;
							}
						}
						color = rgb_to_int(float_to_rgb(255, 255, 255));
					}
				//Final color = Final color + computed color * previous reflection factor;
				//reflection factor = reflection factor * surface reflection property;
				mlx_pixel_put(mlx_ptr, win_ptr, j, i, color);
			}
		}
	}
}


