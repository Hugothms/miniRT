/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:50:51 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 15:43:26 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include"basics.h"

typedef struct		s_ambient_light
{
	float			ratio;
	t_rgb			rgb;
}					t_ambient_light;

typedef struct		s_camera
{
	t_triple		pov;
	t_triple		orientation;
	float			fov;
}					t_camera;

typedef struct		s_light
{
	t_triple		pos;
	float			ratio;
	t_rgb			color;
}					t_light;

typedef struct		s_sphere
{
	t_triple		pos;
	float			diameter;
	t_rgb			color;
}					t_sphere;

typedef struct		s_plane
{
	t_triple		pos;
	t_triple		vect;
	t_rgb			color;
}					t_plane;

typedef struct		s_square
{
	t_triple		pos;
	t_triple		vect;
	float			height;
	t_rgb			color;
}					t_square;

typedef struct		s_cylinder
{
	t_triple		pos;
	t_triple		vect;
	float			diameter;
	float			height;
	t_rgb			color;
}					t_cylinder;

typedef struct		s_triangle
{
	t_triple		p1;
	t_triple		p2;
	t_triple		p3;
	t_rgb			color;
}					t_triangle;

#endif
