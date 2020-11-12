/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/12 17:08:08 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int intersect_disk(const t_ray ray, const t_disk disk, t_impact *impact)
{
	t_vect v;
	double d2;
	t_plane plane;

	plane.pos = disk.pos;
	plane.normal = disk.normal;
	if (intersect_plane(ray, plane, impact))
	{
		impact->pos = multi_vect(add_vect(ray.pos, ray.dir), impact->dist);
		v = sub_vect(impact->pos, disk.pos);
		d2 = dot_product(v, v);
		return (d2 <= disk.radius2);
	}
	return (0);
}

int intersect_cylinder2(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
	t_disk disk;
	disk.pos = cylinder.pos;
	disk.normal = cylinder.dir;
	disk.radius2 = cylinder.radius2;
	if (intersect_disk(ray, disk, impact))
		return (1);
	disk.pos = add_vect(disk.pos, multi_vect(cylinder.dir, cylinder.height));
	if (intersect_disk(ray, disk, impact))
		return (1);

	double a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	double b = 2 * (ray.pos.x * ray.dir.x + ray.pos.z * ray.dir.z);
	double c = ray.pos.x * ray.pos.x + ray.pos.z * ray.pos.z - cylinder.radius2;
	double discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);

	double x1 = (-b + sqrt(discr)) / (2 * a);
	double x2 = (-b - sqrt(discr)) / (2 * a);
	double t;
	//choose the smallest and >=0 t
	if (x1 > x2)
		t = x2;
	if (t < 0)
		t = x1;
	// if both solution are <0 => NO INTERSECTION!
	if (t < 0)
		return (0);
	// normal calculation
	t_vect point = add_vect(ray.pos, multi_vect(ray.dir, t));
	t_vect normal = new_vect(2 * point.x, 0.0f, 2 * point.z);
	//If the y-component from point computed is smaller than 0 or bigger than height => NO INTERSECTION!
	if (point.y < cylinder.pos.y || point.y > cylinder.pos.y + cylinder.height)
		return (0);
	// Intersection in the body cylinder, compute the point and return the intersection
	impact->normal = normal;
	impact->pos = add_vect(ray.pos, multi_vect(ray.dir, t));
	return (1);
}

double intersect_cylinder3(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
	t_vect tmp;
	t_vect tmp2;
	t_vect tmp3;
	t_vect tmp4;
	t_vect abc;
	t_vect delta;

	tmp = sub_vect(ray.dir, multi_vect(cylinder.dir, dot_product(cylinder.dir, ray.dir)));
	tmp2 = sub_vect(ray.pos, cylinder.pos);
	tmp3 = sub_vect(tmp2, multi_vect(cylinder.dir, dot_product(tmp2, cylinder.dir)));
	abc.x = dot_product(tmp, tmp);
	abc.y = 2 * dot_product(tmp, tmp3);
	abc.z = dot_product(tmp3, tmp3) - cylinder.radius2;
	if ((delta.x = abc.y * abc.y - 4 * abc.x * abc.z) < 0)
		return (0);
	delta.y = (-abc.y - sqrt(delta.x)) / (2 * abc.x);
	delta.z = (-abc.y + sqrt(delta.x)) / (2 * abc.x);
	tmp = add_vect(ray.pos, multi_vect(ray.dir, delta.y));
	tmp4 = add_vect(ray.pos, multi_vect(ray.dir, delta.z));
	if (delta.y > 0.00001 && dot_product(cylinder.dir, sub_vect(tmp, cylinder.pos)) > 0 && dot_product(minus_vect(cylinder.dir), sub_vect(tmp, cylinder.pos2)) > 0)
	{
		impact->normal = new_vect(0.0f, 1.0f, 0.0f);
		impact->pos = tmp;
		impact->dist = delta.y;
		return (delta.y);
	}
	if (delta.z > 0.00001 && dot_product(cylinder.dir, sub_vect(tmp4, cylinder.pos)) > 0 && dot_product(minus_vect(cylinder.dir), sub_vect(tmp4, cylinder.pos2)) > 0)
	{
		impact->normal = new_vect(0.0f, 1.0f, 0.0f);
		impact->pos = tmp;
		impact->dist = delta.z;
		return (delta.z);
	}
	return (0);
}

double intersect_cylinder(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
	t_vect	W;
	t_vect	Wn;
	double	w2;
	double	a;
	t_vect	L;
	t_vect	D;
	double	d2;
	double	R;
	t_vect	E;
	double	t;
	t_vect	F;
	t_vect	Fn;
	double	s;
	
	L = sub_vect(ray.pos, cylinder.pos);
	W = cross_product(ray.dir, cylinder.dir);
	w2 = dot_product(W,W);
	if (w2 < EPSILON || w2 > -EPSILON)
	{
		a = dot_product(L, cylinder.dir);
		D = sub_vect(L, multi_vect(cylinder.dir, a));
		d2 = dot_product(D, D);
		if (d2 > cylinder.radius2)
		{
			// printf("1");
			return (0);
		}
		else
			return (1);
	}
	else
	{
		Wn = multi_vect(W, 1 / sqrt(w2));
		R = fabs(dot_product(L, Wn));
		if (R > sqrt(cylinder.radius2))
		{
			// printf("2");
			return (0);
		}
		E = cross_product(L, cylinder.dir);
		t = -dot_product(E,multi_vect(Wn, 1 / sqrt(w2)));
		F = cross_product(Wn, cylinder.dir);
		Fn = multi_vect(F, 1 / distance(new_vect(0,0,0), F));
		s = sqrt(sqrt(cylinder.radius2) - R * R) / fabs(dot_product(ray.dir, Fn));
		if (dot_product(L, cylinder.dir) < sqrt(cylinder.radius2))
		return (t - s);
	}
	return (0);
}

double		cylinder_intersection(const t_ray ray, const t_cylinder cylinder, t_impact *impact);

void ray_cylinders(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list *cylinders;
	t_cylinder *cylinder;
	double tmp;

	cylinders = scene->cylinders;
	while (cylinders->next)
	{
		cylinder = (t_cylinder *)(cylinders->content);
		// if (tmp = intersect_cylinder(ray, *cylinder, impact))
		if (tmp = cylinder_intersection(ray, *cylinder, impact))
		{
			*object = cylinder;
			impact->dist = tmp;
			impact->pos = new_vect(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
			impact->normal = minus_vect(ray.dir);
			//impact->normal = cylinder->normal;
			ft_memcpy(scene->type, "cy\0", 3);
		}
		cylinders = cylinders->next;
	}
}






























double			solve_plane(t_vect o, t_vect d, t_vect plane_p, t_vect plane_nv)
{
	double	x;
	double	denom;

	denom = dot_product(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot_product(plane_nv, sub_vect(plane_p, o))) / denom;
	return (x > 0 ? x : INFINITY);
}

static double	caps_intersection(t_ray ray, const t_cylinder cylinder, t_impact *impact)
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
		return (INFINITY);
	}
	return (INFINITY);
}

static int		solve_cylinder(double x[2], t_ray ray, const t_cylinder cylinder)
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
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

static t_vect		calc_cy_normal(double x2[2], t_ray ray, const t_cylinder cylinder, double dist1, double dist2)
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
	return (normalize(sub_vect(sub_vect(multi_vect(ray.dir, x),	multi_vect(cylinder.dir, dist)), sub_vect(cylinder.pos, ray.pos))));
}

static double	cy_intersection(t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
	double	x2[2];

	if (solve_cylinder(x2, ray, cylinder) == 0)
		return (INFINITY);
	double dist1 = dot_product(cylinder.dir, sub_vect(multi_vect(ray.dir, x2[0]), sub_vect(cylinder.pos, ray.pos)));
	double dist2 = dot_product(cylinder.dir, sub_vect(multi_vect(ray.dir, x2[1]), sub_vect(cylinder.pos, ray.pos)));
	if (!((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) || (dist2 >= 0 && dist2 <= cylinder.height && x2[0] > EPSILON)))
		return (INFINITY);
	impact->pos = calc_cy_normal(x2, ray, cylinder, dist1, dist2);
	impact->normal = sub_vect(cylinder.pos, impact->pos);
	return (x2[0]);
}


double		cylinder_intersection(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
	double	cylinder_inter;
	double	caps_inter;

	cylinder_inter = cy_intersection(ray, cylinder, impact);
	// if (cylinder->texture == 4)
	// 	caps_inter = INFINITY;
	// else
		caps_inter = caps_intersection(ray, cylinder, impact);
	// caps_inter = INFINITY;
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			impact->dist = cylinder_inter;
			// impact->pos = NULL;
			return (1);
		}
		impact->dist = caps_inter;
		// impact->pos = NULL;
		return (1);
	}
	return (0);
}










