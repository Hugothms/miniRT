/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:22:00 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/21 17:31:11 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

# include "../libft/libft.h"

typedef struct		s_couple
{
	int				x;
	int				y;
}					t_couple;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_triple
{
	float			x;
	float			y;
	float			z;
}					t_triple;

typedef struct		s_ray
{
	t_triple		pos;
	t_triple		dir;
}					t_ray;

t_rgb				int_to_rgb(int r, int g, int b);
int					rgb_to_int(t_rgb rgb);
t_rgb				char_to_rgb(char *r, char *g, char *b);
t_ray				new_ray(t_triple position, t_triple direction);

#endif
