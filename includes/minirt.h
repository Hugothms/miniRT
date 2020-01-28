/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:59:45 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/28 14:05:35 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>

# include <unistd.h>

# include "../libft/libft.h"
# include "basics.h"
# include "elements.h"
# include "scene.h"
# include "get_next_line.h"

# define OPEN_ERROR -1
# define CLOSE_ERROR -2
# define PARSE_ERROR -3
# define MLX_ERROR -4
# define MALLOC_ERROR -5

t_scene			*parse(int fd);

/*
** parsing elements
*/
void			set_resolution(t_scene *scene, char **strs);
void			set_ambient_light(t_scene *scene, char **strs);
void			set_camera(t_scene *scene, char **strs);
void			set_light(t_scene *scene, char **strs);
void			set_sphere(t_scene *scene, char **strs);
void			set_plane(t_scene *scene, char **strs);
void			set_square(t_scene *scene, char **strs);
void			set_cylinder(t_scene *scene, char **strs);
void			set_triangle(t_scene *scene, char **strs);


t_rgb			str_to_rgb(char *str);
t_vect			str_to_triple(char *str);
t_vect			set_triple(char *x, char *y, char *z);

void			print_err_and_exit(char *str, int err);

t_vect			new_vect(float x, float y, float z);
t_vect			normalize(t_vect vect);
t_vect			rot_vect(t_vect vect, float angle, char axe);
t_vect			mult_mat(float mat[3][3], t_vect vect);
float			dot_product(t_vect vect1, t_vect vect2);

t_vect			set_vect_dir_cam(t_camera *camera, t_couple resolution, int i, int j);
int				intersect(t_ray ray, t_sphere sphere);

void			print_img(void *mlx_ptr, void *win_ptr,t_scene *scene);

#endif
