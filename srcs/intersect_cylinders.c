/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/16 22:15:50 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		intersect_disk(const t_ray ray, const t_disk disk, t_impact *impact)
{
	t_vect	v; 
	float	d2;
	t_plane	plane;

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

int		intersect_cylinder(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
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

	float x1 = (-b+sqrt(discr))/(2 * a);
	float x2 = (-b-sqrt(discr))/(2 * a);
	float t;
	//choose the smallest and >=0 t
	if (x1 > x2)
		t=x2;
	if (t < 0)
		t=x1;
	// if both solution are <0 => NO INTERSECTION!
	if (t<0)
		return (0);
	// normal calculation
	t_vect point = add_vect(ray.pos, multi_vect(ray.dir, t));
	t_vect normal = new_vect(2 * point.x, 0.0f, 2 * point.z);
	//If the y-component from point computed is smaller than 0 or bigger than height => NO INTERSECTION!
	/*if (point.y < cylinder.pos.y || point.y > cylinder.pos.y + cylinder.height)
		return (0);*/
	//If ray direction is not pararel to Y Plane
	if (ray.dir.y != 0.0f) //Paralel
	{
        //Compute t's for point intersection in the Y Plane
		float t3 = (0-ray.pos.y)/ray.dir.y;
		float t4 = (cylinder.height-ray.pos.y)/ray.dir.y;
		float t2;
		//choose the smallest and >=0 t
		t2 = ft_min_float(t3,t4);
		if (t2 < 0)
			t2 = ft_max_float(t3,t4);
		if (t2 >= 0)
		{
			// If there is a t >= 0 compute de point and check if the point is inside the cap
			t_vect point1 = add_vect(ray.pos, multi_vect(ray.dir, t2));
			if (point1.x*point1.x + point1.z*point1.z <= cylinder.radius2 + 0.9999f)
			{
				// Intersection point is inside cap but, Which t is the smallest? t from cap or t from body cylinder?
				// I choose the smallest t and check if the t is from cap and compute normal and return intersection.
				t = ft_min_float(t,t2);
				if (t == t3)
				{
					impact->normal = new_vect(0.0f,-1.0f,0.0f);
					impact->pos = point1;
					return (1);
				}
				else if (t == t4)
				{
					impact->normal = new_vect(0.0f,1.0f,0.0f);
					impact->pos = point1;
					return (1);
				}
			}
		}
	}
	// Intersection in the body cylinder, compute the point and return the intersection
	impact->normal = normal;
	impact->pos = add_vect(ray.pos, multi_vect(ray.dir, t));
	return (1);
}


int		intersect_cylinder2(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
    return 0;
}

void	ray_cylinders(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*cylinders;
	t_cylinder	*cylinder;

	cylinders = scene->cylinders;
	while (cylinders->next)
	{
		cylinder = (t_cylinder*)(cylinders->content);
		if (intersect_cylinder(ray, *cylinder, impact))
		{
			*object = cylinder;
			//impact->dist = tmp;
			//impact->pos = new_vect(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
			//impact->normal = cylinder->normal;
			ft_memcpy(scene->type, "cy\0", 3);
		}
		cylinders = cylinders->next;
	}
}


double			hit_cylinder(t_cylinder *obj, t_vec3 r, t_vec3 p)
int		intersect_cylinder(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
	t_vect tmp;
	t_vect tmp2;
	t_vect tmp3;
	t_vect abc;
	t_vect delta;

	tmp = sub_vect(r, v3scale(cylinder.dir, dot_product(cylinder.dir, r)));
	tmp2 = sub_vect(p, cylinder.pos);
	tmp3 = sub_vect(tmp2, v3scale(cylinder.dir, dot_product(tmp2, cylinder.dir)));
	abc.x = dot_product(tmp, tmp);
	abc.y = 2 * dot_product(tmp, tmp3);
	abc.z = dot_product(tmp3, tmp3) - obj->radius * obj->radius;
	if ((delta.x = abc.y * abc.y - 4 * abc.x * abc.z) < 0)
		return (NOHIT);
	delta.y = (-abc.y - sqrt(delta.x)) / (2 * abc.x);
	delta.z = (-abc.y + sqrt(delta.x)) / (2 * abc.x);
	tmp = add_vect(p, v3scale(r, delta.y));
	p = add_vect(p, v3scale(r, delta.z));
	if (delta.y > 0.00001 && dot_product(cylinder.dir, sub_vect(tmp, cylinder.pos)) > 0 &&
		dot_product(v3minus(cylinder.dir), sub_vect(tmp, cylinder.pos2)) > 0)
		return (delta.y);
	if (delta.z > 0.00001 && dot_product(cylinder.dir, sub_vect(p, cylinder.pos)) > 0 &&
		dot_product(v3minus(cylinder.dir), sub_vect(p, cylinder.pos2)) > 0)
		return (delta.z);
	return (NOHIT);
}

/*

Ray : P(t) = O + V * t
 Cylinder [O, D, r].
 point Q on cylinder if ((Q - O) x D)^2 = r^2

 Cylinder [A, B, r].
 Point P on infinite cylinder if ((P - A) x (B - A))^2 = r^2 * (B - A)^2
 expand : ((O - A) x (B - A) + t * (V x (B - A)))^2 = r^2 * (B - A)^2
 equation in the form (X + t * Y)^2 = d
 where :
  X = (O - A) x (B - A)
  Y = V x (B - A)
  d = r^2 * (B - A)^2
 expand the equation :
 t^2 * (Y . Y) + t * (2 * (X . Y)) + (X . X) - d = 0
 => second order equation in the form : a*t^2 + b*t + c = 0 where
 a = (Y . Y)
 b = 2 * (X . Y)
 c = (X . X) - d
-----------Vector AB = (B - A);Vector AO = (O - A);Vector AOxAB = (AO ^ AB);
 cross productVector VxAB  = (V ^ AB);
 cross productfloat  ab2   = (AB * AB);
 dot productfloat a      = (VxAB * VxAB);
 dot productfloat b      = 2 * (VxAB * AOxAB);
 dot productfloat c      = (AOxAB * AOxAB) - (r*r * ab2);
 solve second order equation : a*t^2 + b*t + c = 0
 */
