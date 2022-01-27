/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/27 11:33:12 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			solve_plane(t_vect o, t_vect d, t_vect plane_p, t_vect plane_nv)
{
	double	x;
	double	denom;

	denom = dot_product(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot_product(plane_nv, sub_vect(plane_p, o))) / denom;
	return (x > EPSILON ? x : INFINITY);
}

static double	caps_intersection(t_ray ray, const t_cylinder cylinder)
{
	double	id1;
	double	id2;
	t_vect	ip1;
	t_vect	ip2;
	t_vect	c2;

	c2 = add_vect(cylinder.pos, multi_vect(cylinder.dir, cylinder.height));
	id1 = solve_plane(ray.pos, ray.dir, cylinder.pos, cylinder.dir);
	id2 = solve_plane(ray.pos, ray.dir, c2, cylinder.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = add_vect(ray.pos, multi_vect(ray.dir, id1));
		ip2 = add_vect(ray.pos, multi_vect(ray.dir, id2));
		if ((id1 < INFINITY && distance(ip1, cylinder.pos) <= cylinder.radius2) && (id2 < INFINITY && distance(ip2, c2) <= cylinder.radius2))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY && distance(ip1, cylinder.pos) <= cylinder.radius2)
			return (id1);
		else if (id2 < INFINITY && distance(ip2, c2) <= cylinder.radius2)
			return (id2);
	}
	return (INFINITY);
}

static bool	solve_cylinder(double x[2], t_ray ray, const t_cylinder cylinder)
{
	t_vect	v;
	t_vect	u;
	double	a;
	double	b;
	double	c;

	v = multi_vect(cylinder.dir, dot_product(ray.dir, cylinder.dir));
	v = sub_vect(ray.dir, v);
	u = multi_vect(cylinder.dir, dot_product(sub_vect(ray.pos, cylinder.pos), cylinder.dir));
	u = sub_vect(sub_vect(ray.pos, cylinder.pos), u);
	a = dot_product(v, v);
	b = 2 * dot_product(v, u);
	c = dot_product(u, u) - pow(cylinder.radius2, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if (x[0] < EPSILON && x[1] < EPSILON)
		return (0);
	return (1);
}

static void		calc_cy_normal(double x2[2], const t_cylinder cylinder, double dist1, double dist2)
{
	double	dist;
	double	x;

	if ((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) && (dist2 >= 0 && dist2 <= cylinder.height && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? dist1 : dist2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON)
	{
		dist = dist1;
		x = x2[0];
	}
	else
	{
		dist = dist2;
		x = x2[1];
	}
	x2[0] = x;
	// return (normalize(sub_vect(sub_vect(multi_vect(ray.dir, x),	multi_vect(cylinder.dir, dist)), sub_vect(cylinder.pos, ray.pos))));
}

static double	cy_intersection(t_ray ray, const t_cylinder cylinder)
{
	double	x2[2];

	if (!solve_cylinder(x2, ray, cylinder))
		return (INFINITY);
	double dist1 = dot_product(cylinder.dir, sub_vect(multi_vect(ray.dir, x2[0]), sub_vect(cylinder.pos, ray.pos)));
	double dist2 = dot_product(cylinder.dir, sub_vect(multi_vect(ray.dir, x2[1]), sub_vect(cylinder.pos, ray.pos)));
	if (!((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) || (dist2 >= 0 && dist2 <= cylinder.height && x2[0] > EPSILON)))
		return (INFINITY);
	calc_cy_normal(x2, cylinder, dist1, dist2);
	return (x2[0]);
}

double	cylinder_intersection(const t_ray ray, const t_cylinder cylinder, bool *is_on_side)
{
	double	cylinder_inter;
	double	caps_inter;

	cylinder_inter = cy_intersection(ray, cylinder);
	if (!cylinder.is_closed)
		caps_inter = INFINITY;
	else
		caps_inter = caps_intersection(ray, cylinder);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			*is_on_side = true;
			return (cylinder_inter);
		}
		return (caps_inter);
	}
	return (INFINITY);
}

t_vect get_closest_point_from_line(t_vect A, t_vect B, t_vect P)
{
	t_vect AP = sub_vect(P, A);
	t_vect AB = sub_vect(B, A);
	double ab2 = dot_product(AB, AB);
	double ap_ab = dot_product(AP, AB);
	double t = ap_ab / ab2;
	if (t < 0.0)
		t = 0.0;
	else if (t > 1.0)
		t = 1.0;
	return (add_vect(A, multi_vect(AB, t)));
}

void	ray_cylinders(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*cylinders;
	t_cylinder	*cylinder;
	double		tmp;
	bool		is_on_side;

	cylinders = scene->cylinders;
	while (cylinders->next)
	{
		is_on_side = false;
		cylinder = (t_cylinder *)(cylinders->content);
		if ((tmp = cylinder_intersection(ray, *cylinder, &is_on_side)) < impact->dist && tmp > 0)
		{
			*object = cylinder;
			impact->dist = tmp;
			impact->pos = new_vect(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
			if (is_on_side)
				impact->normal = sub_vect(get_closest_point_from_line(cylinder->pos, cylinder->pos2, impact->pos), impact->pos);
			else
				impact->normal = cylinder->dir;
			impact->normal = normalize(impact->normal);
			impact->type = "cy";
		}
		cylinders = cylinders->next;
	}
}
