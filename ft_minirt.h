/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:22:00 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/07 17:49:45 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_pos
{
	float			x;
	float			y;
	float			z;
}					t_pos;

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
}					t_camera;

typedef struct		s_light
{
	t_pos			pos;
	float			ratio;
	t_rgb			color;
}					t_light;

typedef struct		s_sphere
{
	t_pos			pos;
	float			diameter;
	t_rgb			color;
}					t_sphere;

typedef struct		s_plane
{
	t_pos			pos;
	t_pos			vect;
	t_rgb			color;
}					t_plane;

typedef struct		s_sqare
{
	t_pos			pos;
	t_pos			vect;
	float			size;
	t_rgb			color;
}					t_sqare;

typedef struct		s_cylinder
{
	t_pos			pos;
	t_pos			vect;
	float			diameter;
	float			size;
	t_rgb			color;
}					t_cylinder;

typedef struct		s_triangle
{
	t_pos			p1;
	t_pos			p2;
	t_pos			p3;
	t_rgb			color;
}					t_triangle;

typedef struct		s_params
{
	struct s_rgb			rgb;
	struct s_pos			pos;
	struct s_ambient_light	ambient_light;
	struct s_camera			camera;
	struct s_light			light;
	struct s_sphere			sphere;
	struct s_plane			plane;
	struct s_sqare			sqare;
	struct s_cylinder		cylinder;
	struct s_triangle		triangle;
}					t_params;

#endif
