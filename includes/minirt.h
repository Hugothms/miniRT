/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:59:45 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/11 19:24:32 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
#include <time.h>

# include <unistd.h>

# include "../libft/libft.h"
# include "mlxlinux.h"
# include "mlx.h"
# include "basics.h"
# include "elements.h"
# include "scene.h"
# include "get_next_line.h"

# define OPEN_ERROR -1
# define CLOSE_ERROR -2
# define PARSE_ERROR -3
# define MLX_ERROR -4
# define MALLOC_ERROR -5


# define REFLEC 1
# define DEPTH 1

# define ALBEDO 0.3

/*MACOS*/
# define CODE_ESC 53
# define CODE_UP 0
# define CODE_DOWN 0
# define CODE_LEFT 123
# define CODE_RIGHT 124
# define CODE_S 1

/*LINUX*/
# define CODE_ESC 65307
# define CODE_UP 65362
# define CODE_DOWN 65364
# define CODE_LEFT 65361
# define CODE_RIGHT 65363
# define CODE_S 115
 
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

t_vect			new_vect(const float x, const float y, const float z);
t_vect			normalize(t_vect vect);
t_vect			rot_vect(t_vect vect, const float angle, const char axe);
t_vect			mult_mat(const float mat[3][3], t_vect vect);
float			dot_product(const t_vect vect1, const t_vect vect2);
t_vect			add_vect(const t_vect vect1, const t_vect vect2);
t_vect			minus_vect(const t_vect vect);
t_vect			multi_vect(const t_vect vect, float x);

t_vect			set_vect_dir_cam(const t_camera *camera, const t_couple resolution, const int i, const int j);
int				intersect_sphere(const t_ray ray, const t_sphere sphere, t_impact *impact);
void			ray_spheres(const t_ray ray, const t_scene *scene, t_impact *impact, void **object);
int				intersect_plane(const t_ray ray, const t_plane plane, t_impact *impact);
void			ray_planes(const t_ray ray, const t_scene *scene, t_impact *impact, void **object);
float			to_rad(float angle);

void			make_img(t_img *img, const t_scene *scene, const t_camera *camera);
void			save_bmp(const char *filename, const unsigned char *pixels, const t_couple resolution);
void			ft_put_pixel(unsigned char *data, t_couple pixel, int color, t_couple resolution);
char			*screenshot_datetime();
t_scene			*get_scene(const int argc, const char *argv[]);

float			distance(t_vect p1, t_vect p2);
int				solve_quadratic(const t_vect point, float *x0, float *x1);



#endif
