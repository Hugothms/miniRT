/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:59:45 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:16:16 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

# include <unistd.h>

# include "../libft/libft.h"
# include "basics.h"
# include "elements.h"
# include "scene.h"
# include "get_next_line.h"

# define OPEN_ERROR -1
# define CLOSE_ERROR -2
# define PARSE_ERROR -3

t_scene			*parse(int fd);

/*
 ** elements
 */

t_couple		get_resolution(char **strs);
t_ambient_light	get_ambient_light(char **strs);
t_camera		*get_camera(char **strs);
t_light			*get_light(char **strs);
t_sphere		*get_sphere(char **strs);
t_plane			*get_plane(char **strs);
t_square		*get_square(char **strs);
t_cylinder		*get_cylinder(char **strs);
t_triangle		*get_triangle(char **strs);

#endif
