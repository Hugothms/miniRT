/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:22:00 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/12 13:04:58 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

# include "minirt.h"

typedef struct		s_couple
{
	int				w;
	int				h;
}					t_couple;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct		s_ray
{
	double			t;
	t_vect			pos;
	t_vect			dir;
}					t_ray;


typedef struct		s_impact
{
	double			dist;
	t_vect			pos;
	t_vect			normal;
}					t_impact;

t_rgb				*int_to_rgb(int r, int g, int b);
int					rgb_to_int(t_rgb rgb);
t_rgb				char_to_rgb(char *r, char *g, char *b);
t_rgb				*mult_rgb_rgb(t_rgb rgb, t_rgb mult);
t_rgb				*mult_rgb_double(t_rgb rgb, double mult);
t_rgb				*add_rgb_rgb(const t_rgb rgb, const t_rgb add);
void				min_rgb(t_rgb *color);
t_ray				new_ray(const t_vect position, const t_vect direction);
t_rgb				get_color(char *type, void *object);

#endif
