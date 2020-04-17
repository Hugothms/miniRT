/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/17 20:07:24 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int intersect_disk(const t_ray ray, const t_disk disk, t_impact *impact)
{
	t_vect v;
	float d2;
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

	float a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	float b = 2 * (ray.pos.x * ray.dir.x + ray.pos.z * ray.dir.z);
	float c = ray.pos.x * ray.pos.x + ray.pos.z * ray.pos.z - cylinder.radius2;
	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);

	float x1 = (-b + sqrt(discr)) / (2 * a);
	float x2 = (-b - sqrt(discr)) / (2 * a);
	float t;
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

float intersect_cylinder(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
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

void ray_cylinders(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list *cylinders;
	t_cylinder *cylinder;
	float tmp;

	cylinders = scene->cylinders;
	while (cylinders->next)
	{
		cylinder = (t_cylinder *)(cylinders->content);
		if (tmp = intersect_cylinder(ray, *cylinder, impact))
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
