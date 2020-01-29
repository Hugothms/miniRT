/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/29 15:07:44 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int solveQuadratic(const float a, const float b, const float c, float *x0, float *x1)
{
	float	discr;
	float	q;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*x0 = -0.5 * b / a;
		*x1 = -0.5 * b / a;
	}
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
		*x0 = q / a;
		*x1 = c / q;
	}
	if (*x0 > *x1)
		ft_swap(x0, x1);
	return (1);
}

/***
 * check si le ray intersect la sphere et
 * retourne la distance entre le ray et le point de contact s'il y a contact
 ***/
int intersect_sphere(const t_ray ray, const t_sphere sphere)
{
	float	t0;
	float	t1;
	t_vect	dist;

	dist.x = ray.pos.x - sphere.pos.x;
	dist.y = ray.pos.y - sphere.pos.y;
	dist.z = ray.pos.z - sphere.pos.z;
	if (!solveQuadratic(dot_product(ray.dir, ray.dir), 2 * dot_product(ray.dir, dist), dot_product(dist, dist) - sphere.radius, &t0, &t1))
		return (0);
	if (t0 > t1)
		ft_swap(&t0, &t1);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
		return (1);
	}
	return (1);
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
