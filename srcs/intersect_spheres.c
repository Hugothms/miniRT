/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/27 14:10:37 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/***
 * check si le ray intersect la sphere
 * retourne la distance entre le ray et le point de contact s'il y a contact
 ***/
float	intersect_sphere(const t_ray ray, const t_sphere *sphere, t_impact *impact)
{
	float	x0;
	float	x1;
	t_vect	vect;

	vect = new_vect(ray.pos.x - sphere->pos.x, ray.pos.y - sphere->pos.y, ray.pos.z - sphere->pos.z);
	if (!solve_quadratic(new_vect(dot_product(ray.dir, ray.dir), 2 * dot_product(ray.dir, vect), dot_product(vect, vect) - sphere->radius2), &x0, &x1))
		return (INFINITY);
	if (x0 > x1)
		ft_swap(&x0, &x1);
	if (x0 < 0 && x1 < 0)
		return (INFINITY);
	impact->pos = new_vect(ray.pos.x + x1 * ray.dir.x, ray.pos.y + x1 * ray.dir.y, ray.pos.z + x1 * ray.dir.z);
	return (distance(ray.pos, impact->pos));
}

void	ray_spheres(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*spheres;
	t_sphere	*sphere;
	float		tmp;

	spheres = scene->spheres;
	while (spheres->next)
	{
		//determine closest ray/object intersection;
		sphere = (t_sphere*)(spheres->content);
		if ((tmp = intersect_sphere(ray, sphere, impact)) < impact->dist)
		{
			*object = spheres->content;
			impact->dist = tmp;
			impact->pos = new_vect(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
			impact->normal = normalize(new_vect(impact->pos.x - sphere->pos.x, impact->pos.y - sphere->pos.y, impact->pos.z - sphere->pos.z));
			ft_memcpy(scene->type, "sp\0", 3);
		}
		spheres = spheres->next;
	}
}

int		intersect_plane(const t_ray ray, const t_plane plane)
{
	float	denom;
	t_vect	p0l0;

	denom = dot_product(plane.vect, ray.dir);
	if (denom > 1e-6)
	{
		p0l0.x = plane.pos.x - ray.pos.x;
		p0l0.y = plane.pos.y - ray.pos.y;
		p0l0.z = plane.pos.z - ray.pos.z;
		return (dot_product(p0l0, plane.vect) / denom > 0);
	}
	return (0);
}
