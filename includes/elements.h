/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:50:51 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 10:06:53 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include"basics.h"

typedef struct		s_ambient_light
{
	float			ratio;
	t_rgb			rgb;
	float			z;
}					t_ambient_light;

typedef struct		s_camera
{
	t_pos			pov;
	t_pos			vect_or;
	float			fov;
	t_camera		*next;
}					t_camera;

typedef struct		s_light
{
	t_pos			pos;
	float			ratio;
	t_rgb			color;
	t_light			*next;
}					t_light;

typedef struct		s_sphere
{
	t_pos			pos;
	float			diameter;
	t_rgb			color;
	t_sphere		*next;
}					t_sphere;

typedef struct		s_plane
{
	t_pos			pos;
	t_pos			vect;
	t_rgb			color;
	t_plane			*next;
}					t_plane;

typedef struct		s_square
{
	t_pos			pos;
	t_pos			vect;
	float			height;
	t_rgb			color;
	t_square		*next;
}					t_square;

typedef struct		s_cylinder
{
	t_pos			pos;
	t_pos			vect;
	float			diameter;
	float			height;
	t_rgb			color;
	t_cylinder		*next;
}					t_cylinder;

typedef struct		s_triangle
{
	t_pos			p1;
	t_pos			p2;
	t_pos			p3;
	t_rgb			color;
	t_triangle		*next;
}					t_triangle;

#endif
