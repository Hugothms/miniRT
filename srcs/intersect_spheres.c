/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/07 15:31:11 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/***
 * check si le ray intersect la sphere et
 * retourne la distance entre le ray et le point de contact s'il y a contact
 ***/
float	intersect_sphere(const t_ray ray, const t_sphere *sphere, t_impact *impact)
{
	float	x0;
	float	x1;
	t_vect	vect;

	vect = new_vect(ray.pos.x - sphere->pos.x, ray.pos.y - sphere->pos.y, ray.pos.z - sphere->pos.z);
	if (!solve_quadratic(new_vect(dot_product(ray.dir, ray.dir), 2 * dot_product(ray.dir, vect), dot_product(vect, vect) - sphere->radius), &x0, &x1))
		return (INFINITY);
	if (x0 > x1)
		ft_swap(&x0, &x1);
	if (x0 < 0)
	{
		x0 = x1;
		if (x0 < 0)
			return (INFINITY);
		return (distance(new_vect(0, 0, 0), vect));
	}
	return (distance(new_vect(0, 0, 0), vect));
}

/*int	hit_sphere(t_ray ray, t_sphere sphere)
{
	float	a;
	float	b;
	float	delta;
	float	numerator;
	t_vect	dist;

	dist.x = ray.pos.x - sphere.pos.x;
	dist.y = ray.pos.y - sphere.pos.y;
	dist.z = ray.pos.z - sphere.pos.z;
	a = dot_product(ray.dir, ray.dir);
	b = 2.0 * dot_product(dist, ray.dir);
	delta = b * b - 4 * a * dot_product(dist, dist) - sphere.radius * sphere.radius;
	if (delta < 0.0)
		return 0;
	else
	{
		numerator = -b - sqrt(delta);
		if (numerator > 0.0)
			return (numerator / (2.0 * a));
		else
			return 0;
	}
}*/

void	ray_spheres(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*spheres;
	float		tmp;

	spheres = scene->spheres;
	while (spheres->next)
	{
		//determine closest ray/object intersection;
		if ((tmp = intersect_sphere(ray, (t_sphere*)(spheres->content), impact)) < impact->dist)
		{
			impact->dist = tmp;
			*object = spheres->content;
			ft_memcpy(scene->type, "sp\0", 3);
		}
		spheres = spheres->next;
	}
}

int		intersect_plane(const t_ray ray, const t_plane plane)
{
    // assuming vectors are all normalized
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
