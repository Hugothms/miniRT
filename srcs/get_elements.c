/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:08:47 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include<stdio.h>

t_couple		get_resolution(char **strs)
{
	t_couple	resolution;

	printf("get res\n");
	resolution.x = ft_atoi(strs[1]);
	resolution.y = ft_atoi(strs[2]);
	return (resolution);
}

t_ambient_light	get_ambient_light(char **strs)
{
	t_ambient_light	ambient_light;

	printf("get ambient\n");
	ambient_light.ratio = ft_atof(strs[1]);
	ambient_light.rgb = str_to_rgb(strs[2]);
	return (ambient_light);
}

t_camera		*get_camera(char **strs)
{
	t_camera	*camera;

	printf("get camera\n");
	if (!(camera = malloc(sizeof(*camera))))
		return (NULL);
	camera->pov = str_to_triple(strs[1]);
	camera->orientation = str_to_triple(strs[2]);
	camera->fov = ft_atof(strs[3]);
	return (camera);
}

t_light			*get_light(char **strs)
{
	t_light		*light;

	printf("get light\n");
	if (!(light = malloc(sizeof(*light))))
		return (NULL);
	light->pos = str_to_triple(strs[1]);
	light->ratio = ft_atof(strs[2]);
	light->color = str_to_rgb(strs[3]);
	return (light);
}
