/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/24 18:38:48 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vect *mult_mat(float mat[3][3], t_vect *vect)
{
	float	x;
	float	y;
	float	z;

	x = mat[0][0] * vect->x + mat[0][1] * vect->x + mat[0][2] * vect->x;
	y = mat[1][0] * vect->y + mat[1][1] * vect->y + mat[1][2] * vect->y;
	z = mat[2][0] * vect->z + mat[2][1] * vect->z + mat[2][2] * vect->z;
	vect->x = x;
	vect->y = y;
	vect->z = z;
	return (vect);
}

t_vect	*rot_vect(t_vect *vect, float angle, char axe)
{
	//float	mat[3][3];
	float	alpha;

	alpha = (angle / 2) * (M_PI / 180);
	if (axe == 'x')
	{
		float mat[3][3] = {{1, 0, 0}, {0, cos(alpha), -sin(alpha)}, {0, sin(alpha), -cos(alpha)}};
		return(mult_mat(mat, vect));
	}
	else if (axe == 'y')
	{
		float mat[3][3] = {{cos(alpha), 0, sin(alpha)}, {0, 1, 0}, {-sin(alpha), 0, cos(alpha)}};
		return(mult_mat(mat, vect));
	}
	else if (axe == 'z')
	{
		float mat[3][3] = {{cos(alpha), sin(alpha), 0}, {sin(alpha), cos(alpha), 0}, {0, 0, 1}};
		return(mult_mat(mat, vect));
	}
	return (NULL);
}

t_vect	set_orientation_cam(t_camera *camera, t_couple resolution, int i, int j)
{
	t_vect	vect_dir;

	vect_dir = camera->orientation;

	float a = j - (resolution.w - 1) / 2.;
	float b = i - (resolution.h - 1) / 2.;
	float c = resolution.w / (2 * tan((camera->fov / 2) * (M_PI / 180)));

	vect_dir.x = 1 * a + 0 * b + 0 * c;
	vect_dir.y = 0 * a + 1 * b + 0 * c;
	vect_dir.z = 0 * a + 0 * b + 1 * c;

	return (vect_dir);
}

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
			color = rgb_to_int(float_to_rgb(j/4, i/8, (j+i)/12));
			//Ray = { starting point, direction };
			vect_dir = set_orientation_cam(((t_camera*)scene->cameras->next->content) , scene->resolution, i, j);
			//printf("position:\t(%.2f,\t%.2f,\t%.2f)\n",\
													((t_camera*)scene->cameras->next->content)->pos.x,\
													((t_camera*)scene->cameras->next->content)->pos.y,\
													((t_camera*)scene->cameras->next->content)->pos.z);
			printf("direction:%s\t(%.2f,\t%.2f,\t %.2f)\n\n",\
													i  == scene->resolution.h / 2 \
													&& j == scene->resolution.w / 2 ? "\tmiddle\n\n" : "",\
													vect_dir.x,\
													vect_dir.y,\
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


