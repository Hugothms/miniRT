/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_squares.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/25 20:36:05 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	orient(t_vect a, t_vect b, t_vect c, t_vect n)
{
	t_vect	ba;
	t_vect	ca;
	t_vect	normal;
	t_vect	origin;

	ba = sub_vect(b, a),
	ca = sub_vect(c, a);
	origin = new_vect(0, 0, 0);
	normal = new_vect(ba.y * ca.z - ba.z * ca.y, ba.x * ca.z - ba.z * ca.x, ba.y * ca.x - ba.x * ca.y);
	return (dot_product(multi_vect(normal, distance(origin, cross_product(ba, ca))), n));
}

int	intersect_square(const t_ray ray, const t_square square, t_impact *impact)
{
	double		o1;
	double		o2;
	double		o3;
	double		o4;
	t_impact	*impact_plane;
	t_plane		plane;

	plane.pos = square.pos;
	plane.normal = square.normal;
	intersect_plane(ray, plane, impact_plane);
	o1=orient(impact_plane->pos, square.p1, square.p2, square.normal);
	o2=orient(impact_plane->pos, square.p2, square.p3, square.normal);
	o3=orient(impact_plane->pos, square.p3, square.p4, square.normal);
	o4=orient(impact_plane->pos, square.p4, square.p1, square.normal);

	return ((o1 > 0 && o2 > 0 && o3 > 0 && o4 > 0) || (o1 < 0 && o2 < 0 && o3 < 0 && o4 < 0));
}

void	ray_squares(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*squares;
	t_square	*square;

	squares = scene->squares;
	while (squares->next)
	{
		square = (t_square*)(squares->content);
		if (intersect_square(ray, *square, impact))
		{
			*object = square;
			ft_memcpy(scene->type, "sq\0", 3);
		}
		squares = squares->next;
	}
}
