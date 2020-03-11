/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/11 17:06:46 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * retourne la distance entre le ray et le point de contact avec un sphere s'il existe, INFINITY sinon
 **/
int		intersect_sphere(const t_ray ray, const t_sphere sphere, t_impact *impact)
{
	float	x0;
	float	x1;
	t_vect	vect;

	vect = new_vect(ray.pos.x - sphere.pos.x, ray.pos.y - sphere.pos.y, ray.pos.z - sphere.pos.z);
	if (!solve_quadratic(new_vect(dot_product(ray.dir, ray.dir), 2 * dot_product(ray.dir, vect), dot_product(vect, vect) - sphere.radius2), &x0, &x1))
		return (0);
	if ((x0 < 0 && x1 < 0) || (x0 > impact->dist && x1 > impact->dist))
		return (0);
	else if (x0 <= 0.)
		x0 = x1;
	else if (x1 <= 0.)
		x1 = x0;
	impact->dist = ft_min_float(x0, x1);
	impact->pos = add_vect(ray.pos, multi_vect(ray.dir,x1));	
	return (1);
}

void	ray_spheres(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*spheres;
	t_sphere	*sphere;

	spheres = scene->spheres;
	while (spheres->next)
	{
		sphere = (t_sphere*)(spheres->content);
		if (intersect_sphere(ray, *sphere, impact))
		{
			*object = sphere;
			impact->normal = normalize(add_vect(impact->pos, minus_vect(sphere->pos)));
			ft_memcpy(scene->type, "sp\0", 3);
		}
		spheres = spheres->next;
	}
}

int		intersect_plane(const t_ray ray, const t_plane plane, t_impact *impact)
{
	float	denom;
	t_vect	p0l0;
	float	dilat;

	denom = dot_product(plane.normal, ray.dir);
	if (denom > 1e-6)
	{
		p0l0.x = plane.pos.x - ray.pos.x;
		p0l0.y = plane.pos.y - ray.pos.y;
		p0l0.z = plane.pos.z - ray.pos.z;
		if ((dilat = dot_product(p0l0, plane.normal) / denom) > 0)
		{
			impact->normal = plane.normal;
			impact->pos = add_vect(ray.pos, multi_vect(ray.dir,dilat));
			impact->dist = distance(ray.pos, impact->pos);
			return (1);
		}		
	}
	return (0);
}

void	ray_planes(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*planes;
	t_plane		*plane;
	float		tmp;

	planes = scene->planes;
	while (planes->next)
	{
		plane = (t_plane*)(planes->content);
		if ((tmp = intersect_plane(ray, *plane, impact)))
		{
			*object = plane;
			//impact->dist = tmp;
			//impact->pos = new_vect(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
			impact->normal = plane->normal;
			ft_memcpy(scene->type, "pl\0", 3);
		}
		planes = planes->next;
	}
}