/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:49:41 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/28 14:05:19 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vect		new_vect(float x, float y, float z)
{
	t_vect	new;

	new.x = x;
	new.x = y;
	new.x = z;
	return (new);
}

t_vect		normalize(t_vect vect)
{
	float	length;

	length = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	vect.x = vect.x / length;
	vect.y = vect.y / length;
	vect.z = vect.z / length;
	return (vect);
}

t_vect		mult_mat(float mat[3][3], t_vect vect)
{
	float	x;
	float	y;
	float	z;

	x = mat[0][0] * vect.x + mat[0][1] * vect.x + mat[0][2] * vect.x;
	y = mat[1][0] * vect.y + mat[1][1] * vect.y + mat[1][2] * vect.y;
	z = mat[2][0] * vect.z + mat[2][1] * vect.z + mat[2][2] * vect.z;
	vect = new_vect(x, y, z);
	return (vect);
}


t_vect		rot_vect(t_vect vect, float angle, char axe)
{
	float	alpha;

	alpha = (angle * 0.5) * (M_PI / 180);
	if (axe == 'x')
		return(mult_mat((float[3][3]){{1, 0, 0}, {0, cos(alpha), -sin(alpha)}, {0, sin(alpha), -cos(alpha)}}, vect));
	else if (axe == 'y')
		return(mult_mat((float[3][3]){{cos(alpha), 0, sin(alpha)}, {0, 1, 0}, {-sin(alpha), 0, cos(alpha)}}, vect));
	else if (axe == 'z')
		return(mult_mat((float[3][3]){{cos(alpha), sin(alpha), 0}, {sin(alpha), cos(alpha), 0}, {0, 0, 1}}, vect));
	return (new_vect(0, 0, 0));
}

float		dot_product(t_vect vect1, t_vect vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z *vect2.z);
}