/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:59:45 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/26 21:07:33 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/includes/libft.h"
# include "mlx.h"
# include "basics.h"
# include "elements.h"
# include "scene.h"
# include "parse.h"

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <time.h>
# include <unistd.h>
# include <stdbool.h>
#include <stdio.h>

# ifndef THREADS
#  define THREADS 1
# endif

# define OPEN_ERROR -1
# define CLOSE_ERROR -2
# define PARSE_ERROR -3
# define MLX_ERROR -4
# define MALLOC_ERROR -5

# define REFLEC 1
# define DEPTH 1

# define ALBEDO 0.3
# define EPSILON 1e-4

/*
** Keycodes and screen size LINUX and MAC
*/
# ifdef LINUX
#  define ESC		65307
#  define LEFT		65361
#  define RIGHT		65363
#  define KEY_S		115
#  define KEY_Q		113
# else
#  define ESC		53
#  define LEFT		123
#  define RIGHT		124
#  define UP		126
#  define DOWN		125
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_W		13
#  define KEY_Q		12
#  define KEY_E		14
#  define KEY_J		38
#  define KEY_K		40
#  define KEY_L		37
#  define KEY_I		34
#  define KEY_U		32
#  define KEY_O		31
#  define KEY_SPACE	49
#  define KEY_PLUS	69
#  define KEY_MINUS	78
# endif

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_img
{
	void			*img_ptr;
 	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned char	*data;
}					t_img;

typedef struct	s_window
{
	t_mlx		*mlx;
	t_img		*img;
	t_scene		*scene;
}				t_window;






/**
 * parsing
**/
t_scene			*parse(int fd);
void			set_resolution(t_scene *scene, char **strs);
void			set_ambient_light(t_scene *scene, char **strs);
void			set_camera(t_scene *scene, char **strs);
void			set_light(t_scene *scene, char **strs);
void			set_sphere(t_scene *scene, char **strs);
void			set_plane(t_scene *scene, char **strs);
void			set_square(t_scene *scene, char **strs);
void			set_cylinder(t_scene *scene, char **strs);
void			set_triangle(t_scene *scene, char **strs);

t_rgb			str_to_rgb(const char *str);
t_vect			str_to_vect(const char *str);
t_vect			set_vect(const char *x, const char *y, const char *z);


/**
 * vectors
**/
t_vect			new_vect(const double x, const double y, const double z);
t_vect			normalize(const t_vect vect);
t_vect			rot_vect(const t_vect vect, const double angle, const char axe);
t_vect			mult_mat(const double mat[3][3], t_vect vect);
double			dot_product(const t_vect vect1, const t_vect vect2);
t_vect			add_vect(const t_vect vect1, const t_vect vect2);
t_vect			sub_vect(const t_vect vect1, const t_vect vect2);
t_vect			minus_vect(const t_vect vect);
t_vect			multi_vect(const t_vect vect, const double x);
t_vect			cross_product(const t_vect v1, const t_vect v2);

t_vect			set_vect_dir_cam(const t_camera *camera, const t_couple resolution, const int i, const int j);
bool			intersect_plane(const t_ray ray, const t_plane plane, t_impact *impact);
void			ray_cylinders(const t_ray ray, t_scene *scene, t_impact *impact, void **object);
void			ray_planes(const t_ray ray, const t_scene *scene, t_impact *impact, void **object);
void			ray_spheres(const t_ray ray, const t_scene *scene, t_impact *impact, void **object);
void			ray_squares(const t_ray ray, const t_scene *scene, t_impact *impact, void **object);
void			ray_triangles(const t_ray ray, const t_scene *scene, t_impact *impact, void **object);
double			to_rad(const double angle);

void			make_img(t_img *img, const t_scene *scene, const t_camera *camera);
void			save_bmp(const char *filename, const unsigned char *pixels, const t_couple resolution);
void			ft_put_pixel(unsigned char *data, t_couple pixel, int color, t_couple resolution);
char			*screenshot_datetime();
t_scene			*get_scene(const int argc, char *argv[]);

void			print_err_and_exit(const char *str, const int err);

double			distance(const t_vect p1, const t_vect p2);
bool			solve_quadratic(const t_vect point, double *x0, double *x1);
int             ft_tab_size(char **tab);

#endif
