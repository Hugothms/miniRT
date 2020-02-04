/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:51:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/04 19:17:49 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vect		set_triple(char *x, char *y, char *z)
{
	t_vect	triple;

	triple.x = ft_atof(x);
	triple.y = ft_atof(y);
	triple.z = ft_atof(z);
	return (triple);
}

t_vect		str_to_triple(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return (set_triple(tab[0], tab[1], tab[2]));
}

t_rgb		str_to_rgb(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return (char_to_rgb(tab[0], tab[1], tab[2]));
}

float	to_rad(float angle)
{
	return (angle * M_PI * 0.5);
}

t_ray		new_ray(const t_vect position, const t_vect direction)
{
	t_ray	ray;

	ray.pos = position;
	ray.dir = direction;
	return (ray);
}

t_vect		set_vect_dir_cam(const t_camera *camera, const t_couple resolution, const int i, const int j)
{
	t_vect	vect_dir;
	float	a;
	float	b;
	float	c;
	int		max;

	a = j + 0.5 - (resolution.w) * 0.5;
	b = i + 0.5 - (resolution.h) * 0.5;
	max = resolution.w > resolution.h ? resolution.w : resolution.h;
	c = max / (2 * tan((to_rad(camera->fov)) / 180.0));
	vect_dir.x = 1 * a + 0 * b + 0 * c;
	vect_dir.y = 0 * a + 1 * b + 0 * c;
	vect_dir.z = 0 * a + 0 * b + 1 * c;
	// vect unitaires de la camera

	//vect_dir = rot_vect(vect_dir, camera->fov * 0.5, 'x');
	//vect_dir = rot_vect(vect_dir, camera->fov * 0.5, 'y');
	//vect_dir = rot_vect(vect_dir, camera->fov * 0.5, 'z');

	// g_data->ray.dir.x = coord[0] - (g_data->render[0] / 2) * tmp.x;
    // g_data->ray.dir.y = coord[1] - (g_data->render[1] / 2) * tmp.y;
    // g_data->ray.dir.z = tmp.z * (-g_data->render[1] / (2 * tan((to_rad(g_data->cam->fov) / 2))))
	return (normalize(vect_dir));
}
