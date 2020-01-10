/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 20:41:28 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_triple		set_triple(char *x, char *y, char *z)
{
	t_triple	triple;

	triple.x = ft_atof(x);
	triple.y = ft_atof(y);
	triple.z = ft_atof(z);
	return (triple);
}

t_triple		str_to_triple(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return (set_triple(tab[0], tab[1], tab[2]));
}

t_rgb		str_to_rgb(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return (set_rgb(tab[0], tab[1], tab[2]));
}

void	init_scene(t_scene *scene)
{
	scene->resolution = NULL;
	scene->ambient_light = NULL;
	scene->cameras = ft_lstnew(NULL);
	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->squares = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
	scene->triangles = ft_lstnew(NULL);
}

t_scene			*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	*set;
	char	**data;

	set = " \t";
	if (!(scene = malloc(sizeof(*scene))))
		return (NULL);
	init_scene(scene);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		printf("\n|%s|\n", line);
		data = ft_split_set((*line ? line : "iamcheating"), set);
		if (!ft_strcmp(data[0], "R") && !scene->resolution)
			set_resolution(scene, data);
		else if (!ft_strcmp(data[0], "A") && in_charset(line[1], set))
			set_ambient_light(scene, data);
		else if (!ft_strcmp(data[0], "c") && in_charset(line[1], set))
			set_camera(scene, data);
		else if (!ft_strcmp(data[0], "l") && in_charset(line[1], set))
			set_light(scene, data);
		else if (!ft_strcmp(data[0], "sp") && in_charset(line[2], set))
			set_sphere(scene, data);
		else if (!ft_strcmp(data[0], "pl") && in_charset(line[2], set))
			set_plane(scene, data);
		else if (!ft_strcmp(data[0], "sq") && in_charset(line[2], set))
			set_square(scene, data);
		else if (!ft_strcmp(data[0], "cy") && in_charset(line[2], set))
			set_cylinder(scene, data);
		else if (!ft_strcmp(data[0], "tr") && in_charset(line[2], set))
			set_triangle(scene, data);
		else if (!ft_is_from_charset(line, set))
		{
			free(line);
			ft_putstr("Error\n");
			return (NULL);
		}
		free(line);
	}
	return (scene);
}
