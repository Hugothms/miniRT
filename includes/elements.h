/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:50:51 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/12 13:04:58 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "basics.h"

typedef struct		s_ambient_light
{
	double			ratio;
	t_rgb			color;
}					t_ambient_light;

typedef struct		s_camera
{
	t_vect			pos;
	t_vect			orientation;
	t_vect			up;
	double			fov;
}					t_camera;

typedef struct		s_light
{
	t_vect			pos;
	double			ratio;
	t_rgb			color;
}					t_light;

typedef struct		s_sphere
{
	t_vect			pos;
	double			radius2;
	t_rgb			color;
	double			reflec;
}					t_sphere;

typedef struct		s_plane
{
	t_vect			pos;
	t_vect			normal;
	t_rgb			color;
}					t_plane;

typedef struct		s_square
{
	t_vect			pos;
	t_vect			normal;
	double			height;
	t_vect			p1;
	t_vect			p2;
	t_vect			p3;
	t_vect			p4;
	t_rgb			color;
}					t_square;

typedef struct		s_cylinder
{
	t_vect			pos;
	t_vect			pos2;
	t_vect			dir;
	double			radius2;
	double			height;
	t_rgb			color;
}					t_cylinder;

typedef struct		s_disk
{
	t_vect			pos;
	t_vect			normal;
	double			radius2;
	t_rgb			color;
}					t_disk;

typedef struct		s_triangle
{
	t_vect			v0;
	t_vect			v1;
	t_vect			v2;
	t_rgb			color;
}					t_triangle;

#endif
