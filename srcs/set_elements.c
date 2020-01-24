/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/23 15:45:01 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			check_resolution(char **data)
{
	if (ft_atoi(data[1]) <= 0 || ft_atoi(data[2]) <= 0)
		return (-1);
	return (0);
}

void		set_resolution(t_scene *scene, char **data)
{
	t_couple	*resolution;

	printf("set res\n");
	if (check_resolution(data))
		print_err_and_exit("resolution (R) must be 2 positive numbers", 20);
	if (!(resolution = malloc(sizeof(*resolution))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	resolution->w = ft_atoi(data[1]);
	resolution->h = ft_atoi(data[2]);
	scene->resolution = *resolution;
}

void		set_ambient_light(t_scene *scene, char **data)
{
	t_ambient_light	*ambient_light;

	printf("set ambient\n");
	if (!(ambient_light = malloc(sizeof(*ambient_light))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ambient_light->ratio = ft_atof(data[1]);
	ambient_light->rgb = str_to_rgb(data[2]);
	scene->ambient_light = *ambient_light;
}

void	set_camera(t_scene *scene, char **data)
{
	t_camera	*camera;

	printf("set camera\n");
	if (!(camera = malloc(sizeof(*camera))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	camera->pos = str_to_triple(data[1]);
	camera->orientation = str_to_triple(data[2]);
	camera->fov = ft_atof(data[3]);
	ft_lstadd_back(&(scene->cameras), ft_lstnew(camera));
}

void		set_light(t_scene *scene, char **data)
{
	t_light		*light;

	printf("set light\n");
	if (!(light = malloc(sizeof(*light))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	light->pos = str_to_triple(data[1]);
	light->ratio = ft_atof(data[2]);
	light->color = str_to_rgb(data[3]);
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}
