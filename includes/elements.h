/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:50:51 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/25 17:46:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "basics.h"

typedef struct		s_ambient_light
{
	float			ratio;
	t_rgb			color;
}					t_ambient_light;

typedef struct		s_camera
{
	t_vect			pos;
	t_vect			orientation;
	t_vect			up;
	float			fov;
}					t_camera;

typedef struct		s_light
{
	t_vect			pos;
	float			ratio;
	t_rgb			color;
}					t_light;

typedef struct		s_sphere
{
	t_vect			pos;
	float			radius2;
	t_rgb			color;
}					t_sphere;

typedef struct		s_plane
{
	t_vect			pos;
	t_vect			vect;
	t_rgb			color;
}					t_plane;

typedef struct		s_square
{
	t_vect			pos;
	t_vect			vect;
	float			height;
	t_rgb			color;
}					t_square;

typedef struct		s_cylinder
{
	t_vect			pos;
	t_vect			vect;
	float			diameter;
	float			height;
	t_rgb			color;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vect			p1;
	t_vect			p2;
	t_vect			p3;
	t_rgb			color;
}					t_triangle;

#endif
