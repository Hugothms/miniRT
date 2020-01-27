/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/27 17:45:21 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		solveQuadratic(float a, float b, float c, float *x0, float *x1)
{
	float	discr;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*x0 = - 0.5 * b / a;
		*x1 = - 0.5 * b / a;
	}
	else
	{
		float q = (b > 0) ?	- 0.5 * (b + sqrt(discr)) :	- 0.5 * (b - sqrt(discr));
		*x0 = q / a;
		*x1 = c / q;
	}
	if (*x0 > *x1) ft_swap(x0, x1);

	return (1);
}

int		intersect(t_ray ray, t_sphere sphere)
{
	float	*t0;
	float	*t1;
	t_vect	L;

	L.x = ray.pos.x - sphere.pos.x;
	L.y = ray.pos.y - sphere.pos.y;
	L.z = ray.pos.z - sphere.pos.z;
	if (!solveQuadratic(dotProduct(ray.dir, ray.dir), 2 * dotProduct(ray.dir, L), dotProduct(L, L) - sphere.radius, t0, t1))
		return (0);
	if (t0 > t1)
		ft_swap(t0, t1);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
	}
	return (1);
}