/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:53:11 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/14 17:47:28 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		set_sphere(t_scene *scene, char **strs)
{
	t_sphere	*sphere;
	float		radius;

	if (!(sphere = malloc(sizeof(*sphere))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	sphere->pos = str_to_triple(strs[1]);
	radius = ft_atof(strs[2]);
	sphere->radius2 = radius * radius;
	sphere->color = str_to_rgb(strs[3]);
	sphere->reflec = 0;
	if (strs[4])
		sphere->reflec = ft_atof(strs[4]);
	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
}

void		set_plane(t_scene *scene, char **strs)
{
	t_plane		*plane;

	if (!(plane = malloc(sizeof(*plane))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	plane->pos = str_to_triple(strs[1]);
	plane->normal = normalize(str_to_triple(strs[2]));
	plane->color = str_to_rgb(strs[3]);
	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
}

void		set_cylinder(t_scene *scene, char **strs)
{
	t_cylinder	*cylinder;
	float		radius;

	if (!(cylinder = malloc(sizeof(*cylinder))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	cylinder->pos = str_to_triple(strs[1]);
	cylinder->dir = normalize(str_to_triple(strs[2]));
	radius = ft_atof(strs[3]) / 2;
	cylinder->radius2 = radius * radius;
	cylinder->height = ft_atof(strs[4]);
	cylinder->color = str_to_rgb(strs[5]);
	ft_lstadd_front(&(scene->cylinders), ft_lstnew(cylinder));
}
void		set_square_points(t_scene *scene, t_square *square)
{
	t_camera	camera;
	
	camera = *(t_camera*)scene->cameras->content;
	square->height / 2;
	square->pos;
	square->normal;
	// square->p1 = new_vect(-1, -1, 6);
	// square->p2 = new_vect(1, -1, 6);
	// square->p3 = new_vect(-1, -1, 4);
	// square->p4 = new_vect(1, -1, 4);
}

void		set_square(t_scene *scene, char **strs)
{
	t_square	*square;

	if (!(square = malloc(sizeof(*square))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	square->pos = str_to_triple(strs[1]);
	square->normal = normalize(str_to_triple(strs[2]));
	square->height = ft_atof(strs[3]);
	square->color = str_to_rgb(strs[4]);
	set_square_points(scene, square);
	ft_lstadd_front(&(scene->squares), ft_lstnew(square));
}

void		set_triangle(t_scene *scene, char **strs)
{
	t_triangle	*triangle;

	if (!(triangle = malloc(sizeof(*triangle))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	triangle->v0 = str_to_triple(strs[1]);
	triangle->v1 = str_to_triple(strs[2]);
	triangle->v2 = str_to_triple(strs[3]);
	triangle->color = str_to_rgb(strs[4]);
	ft_lstadd_front(&(scene->triangles), ft_lstnew(triangle));
}
