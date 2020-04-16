/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:49:41 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/16 22:11:12 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vect		new_vect(const float x, const float y, const float z)
{
	t_vect	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

float	distance(const t_vect p1, const t_vect p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}

t_vect		normalize(const t_vect vect)
{
	float	length;

	length = distance(new_vect(0,0,0), vect);
	return (new_vect(vect.x / length, vect.y / length, vect.z / length));
}

t_vect		mult_mat(const float mat[3][3], const t_vect vect)
{
	float	x;
	float	y;
	float	z;
	t_vect	res;

	x = mat[0][0] * vect.x + mat[0][1] * vect.x + mat[0][2] * vect.x;
	y = mat[1][0] * vect.y + mat[1][1] * vect.y + mat[1][2] * vect.y;
	z = mat[2][0] * vect.z + mat[2][1] * vect.z + mat[2][2] * vect.z;
	res = new_vect(x, y, z);
	return (res);
}

t_vect		rot_vect(const t_vect vect, const float angle, const char axe)
{
	float	alpha;

	alpha = to_rad(angle * 0.5);
	if (axe == 'x')
		return (mult_mat((float[3][3]){{1, 0, 0}, {0, cos(alpha), -sin(alpha)}, {0, sin(alpha), -cos(alpha)}}, vect));
	else if (axe == 'y')
		return (mult_mat((float[3][3]){{cos(alpha), 0, sin(alpha)}, {0, 1, 0}, {-sin(alpha), 0, cos(alpha)}}, vect));
	else if (axe == 'z')
		return (mult_mat((float[3][3]){{cos(alpha), sin(alpha), 0}, {sin(alpha), cos(alpha), 0}, {0, 0, 1}}, vect));
	return (new_vect(0, 0, 0));
}

t_vect		add_vect(const t_vect vect1, const t_vect vect2)
{
	return (new_vect(vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z));
}

t_vect		sub_vect(const t_vect vect1, const t_vect vect2)
{
	return (new_vect(vect1.x - vect2.x, vect1.y - vect2.y, vect1.z - vect2.z));
}

t_vect		minus_vect(const t_vect vect)
{
	return (new_vect(-vect.x, -vect.y, -vect.z));
}

t_vect		multi_vect(const t_vect vect, const float x)
{
	return (new_vect(vect.x * x, vect.y * x, vect.z * x));
}

float		dot_product(const t_vect vect1, const t_vect vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z *vect2.z);
}

t_vect		cross_product(t_vect v1, t_vect v2)
{
	t_vect	origin;
	t_vect	normal;
	float	denom;
	float	cross;

	origin = new_vect(0, 0, 0);
	denom = distance(origin, v1) * distance(origin, v2);
	cross = denom * sinf(acos(dot_product(v1, v2) / denom));
	normal = new_vect(v1.y * v2.z - v1.z * v2.y, v1.x * v2.z - v1.z * v2.x, v1.y * v2.x - v1.x * v2.y);
	return (multi_vect(normal, cross));
}