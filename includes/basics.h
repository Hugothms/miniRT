/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:22:00 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 16:40:45 by hthomas          ###   ########.fr       */
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
	char			r;
	char			g;
	char			b;
}					t_rgb;

typedef struct		s_triple
{
	float			x;
	float			y;
	float			z;
}					t_triple;

t_rgb	ft_t_rgb(int r, int g, int b);
int		ft_rgb(t_rgb rgb);
t_rgb	set_rgb(char r, char g, char b);

#endif