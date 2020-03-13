/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/13 15:38:29 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		check_resolution(char **data)
{
	if (ft_atoi(data[1]) <= 0 || ft_atoi(data[2]) <= 0)
		return (-1);
	return (0);
}

void	set_resolution(t_scene *scene, char **data)
{
	t_couple	*resolution;

	if (check_resolution(data))
		print_err_and_exit("resolution (R) must be 2 positive numbers", 20);
	if (!(resolution = malloc(sizeof(*resolution))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	resolution->w = ft_min_int(ft_atoi(data[1]), MAX_W);
	resolution->h = ft_min_int(ft_atoi(data[2]), MAX_H);
	scene->resolution = *resolution;
}

void	set_ambient_light(t_scene *scene, char **data)
{
	t_ambient_light	*ambient_light;
	float			ratio;

	if (!(ambient_light = malloc(sizeof(*ambient_light))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ratio = ft_atof(data[1]);
	ambient_light->color = *mult_rgb_float(str_to_rgb(data[2]), ratio);
	scene->ambient_light = *ambient_light;
}

void	set_camera(t_scene *scene, char **data)
{
	t_camera	*camera;

	if (!(camera = malloc(sizeof(*camera))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	camera->pos = str_to_triple(data[1]);
	camera->orientation = normalize(str_to_triple(data[2]));
	camera->up = new_vect(0, 1, 0);
	camera->fov = ft_atof(data[3]);
	ft_lstadd_front(&(scene->cameras), ft_lstnew(camera));
}

void	set_light(t_scene *scene, char **data)
{
	t_light		*light;
	int			ratio;

	if (!(light = malloc(sizeof(*light))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	light->pos = str_to_triple(data[1]);
	ratio = ft_atof(data[2]) * 255;
	light->color = *mult_rgb_float(str_to_rgb(data[3]), ratio);
	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
}
