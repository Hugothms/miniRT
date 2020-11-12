/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/12 13:04:58 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		intersect_plane(const t_ray ray, const t_plane plane, t_impact *impact)
{
	double	denom;
	double	x;

	denom = dot_product(plane.normal, ray.dir);
	if (fabs(denom) > 0)
	{
		x = dot_product(sub_vect(plane.pos, ray.pos), plane.normal) / denom;
		// printf("\t/\t%.2f\t%.2f", x, impact->dist);
		if (x > EPSILON && x < impact->dist)
		{
			// printf("i");
			impact->normal = plane.normal;
			impact->pos = add_vect(ray.pos, multi_vect(ray.dir, x));
			impact->pos = add_vect(impact->pos, multi_vect(impact->normal, EPSILON));
			impact->dist = x;
			// printf("\t%.2f", impact->dist);
			return (1);
		}
	}
	return (0);
}

void	ray_planes(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*planes;
	t_plane		*plane;

	planes = scene->planes;
	while (planes->next)
	{
		plane = (t_plane*)(planes->content);
		if (intersect_plane(ray, *plane, impact))
		{
			*object = plane;
			ft_memcpy(scene->type, "pl\0", 3);
		}
		planes = planes->next;
	}
}
