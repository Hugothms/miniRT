/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:22:00 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 09:59:24 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

# include "../libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>

# include <unistd.h>

typedef struct		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

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

typedef struct		s_pos
{
	float			x;
	float			y;
	float			z;
}					t_pos;

#endif