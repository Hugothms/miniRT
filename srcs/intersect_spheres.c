/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/15 18:12:05 by hthomas          ###   ########.fr       */
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
	impact->normal = normalize(add_vect(impact->pos, minus_vect(sphere.pos)));
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

int		intersect_plane(const t_ray ray, const t_plane plane, t_impact *impact)
{
	float	denom;
	t_vect	p0l0;
	float	x;

	denom = dot_product(plane.normal, ray.dir);
	if (fabs(denom) > EPSILON)
	{
		x = dot_product(add_vect(plane.pos, minus_vect(ray.pos)), plane.normal) / denom;
		if (x > 0 && x < impact->dist)
		{
			impact->normal = plane.normal;
			impact->pos = add_vect(ray.pos, multi_vect(ray.dir, x));
			impact->pos = add_vect(impact->pos, multi_vect(impact->normal, EPSILON));
			impact->dist = x;
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


int		intersect_cylinder(const t_ray ray, const t_cylinder cylinder, t_impact *impact)
{
    // R(t) = o + td
    // x² + z² = r²
    // (ox+tdx)² + (oz+tdz)² = r²
    // (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
    // t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
    // a=(dx + dz); b = 2(oxdx + ozdz); c = (ox)² + (oz)² - r²
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
    // f(x,y) = x² + z² - r² = 0
    // T = (dx/dt, y, dz/dt)
    // 0 = df/dt = (df/dx, y, df/dz) · T
    // N = (2x, 0, 2z)
    t_vect point = add_vect(ray.pos, multi_vect(ray.dir, t));
    t_vect normal = new_vect(2*point.x, 0.0f, 2*point.z);
    // If the y-component from point computed is smaller than 0 or bigger than height => NO INTERSECTION!
    if (point.y < 0 || point.y > cylinder.height)
        return (0);
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
            //std::cout << "point " << point1.y << " hipo " << point1.x*point1.x + point1.z*point1.z << " radio " << cylinder.radius2 << std::endl;
            if (point1.x*point1.x + point1.z*point1.z <= cylinder.radius2 + 0.9f)
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
    impact->normal = new_vect(0.0f,1.0f,0.0f);
	impact->pos = add_vect(ray.pos, multi_vect(ray.dir, t));
    return (1);
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


float	orient(t_vect a, t_vect b, t_vect c, t_vect n)
{	
	t_vect	new;
	
	new = add_vect(b, minus_vect(a)), add_vect(c, minus_vect(a));
	return (new.x * n.y + new.y * n.z + new.z * n.x);
}

int		intersect_square(const t_ray ray, const t_square square, t_impact *impact)
{
	float		o1;
	float		o2;
	float		o3;
	float		o4;
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
