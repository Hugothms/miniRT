/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:51:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/27 17:43:08 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vect		new_vect(float x, float y, float z)
{
	t_vect	new;

	new.x = x;
	new.x = y;
	new.x = z;
	return (new);
}

t_vect		normalize(t_vect vect)
{
	float	length;

	length = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	vect.x = vect.x / length;
	vect.y = vect.y / length;
	vect.z = vect.z / length;
	return (vect);
}

t_ray		new_ray(t_vect position, t_vect direction)
{
	t_ray	ray;

	ray.pos = position;
	ray.dir = direction;
	return ray;
}


t_vect		mult_mat(float mat[3][3], t_vect vect)
{
	float	x;
	float	y;
	float	z;

	x = mat[0][0] * vect.x + mat[0][1] * vect.x + mat[0][2] * vect.x;
	y = mat[1][0] * vect.y + mat[1][1] * vect.y + mat[1][2] * vect.y;
	z = mat[2][0] * vect.z + mat[2][1] * vect.z + mat[2][2] * vect.z;
	vect = new_vect(x, y, z);
	return (vect);
}

t_vect		rot_vect(t_vect vect, float angle, char axe)
{
	float	alpha;

	alpha = (angle * 0.5) * (M_PI / 180);
	if (axe == 'x')
		return(mult_mat((float[3][3]){{1, 0, 0}, {0, cos(alpha), -sin(alpha)}, {0, sin(alpha), -cos(alpha)}}, vect));
	else if (axe == 'y')
		return(mult_mat((float[3][3]){{cos(alpha), 0, sin(alpha)}, {0, 1, 0}, {-sin(alpha), 0, cos(alpha)}}, vect));
	else if (axe == 'z')
		return(mult_mat((float[3][3]){{cos(alpha), sin(alpha), 0}, {sin(alpha), cos(alpha), 0}, {0, 0, 1}}, vect));
	return (new_vect(0, 0, 0));
}

t_vect		set_vect_dir_cam(t_camera *camera, t_couple resolution, int i, int j)
{
	t_vect	vect_dir;

	float a = j + 0.5 - (resolution.w) * 0.5;
	float b = i + 0.5 - (resolution.h) * 0.5;
	float c = resolution.w / (2 * tan((camera->fov * 0.5) * (M_PI / 180)));

	vect_dir.x = 1 * a + 0 * b + 0 * c;
	vect_dir.y = 0 * a + 1 * b + 0 * c;
	vect_dir.z = 0 * a + 0 * b + 1 * c;
	// vect unitaires de la camera

	//vect_dir = rot_vect(vect_dir, camera->fov * 0.5, 'x');
	//vect_dir = rot_vect(vect_dir, camera->fov * 0.5, 'y');
	//vect_dir = rot_vect(vect_dir, camera->fov * 0.5, 'z');
	return (normalize(vect_dir));
}
