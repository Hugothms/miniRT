/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:51:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/28 13:51:21 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray		new_ray(t_vect position, t_vect direction)
{
	t_ray	ray;

	ray.pos = position;
	ray.dir = direction;
	return ray;
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
