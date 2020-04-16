/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/16 22:16:19 by hthomas          ###   ########.fr       */
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
	impact->pos = add_vect(ray.pos, multi_vect(ray.dir, x1));
	impact->normal = normalize(sub_vect(impact->pos, sphere.pos));
	impact->pos = add_vect(impact->pos, multi_vect(impact->normal, EPSILON));
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
			ft_memcpy(scene->type, "sp\0", 3);
		}
		spheres = spheres->next;
	}
}
