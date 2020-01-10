/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:14:47 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include<stdio.h>

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
	return (set_rgb("tab[0]", "tab[1]", "tab[2]"));
}

void	init_scene(t_scene *scene)
{
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

	set = " \t";
	if (!(scene = malloc(sizeof(*scene))))
		return (NULL);
	init_scene(scene);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		printf("\n|%s|\n", line);
		if (!ft_strncmp(line, "R", 1) && in_charset(line[1], set))
			scene->resolution = get_resolution(ft_split_set(line, set));
		else if (!ft_strncmp(line, "A", 1) && in_charset(line[1], set))
			scene->ambient_light = get_ambient_light(ft_split_set(line, set));
		else if (!ft_strncmp(line, "c", 1) && in_charset(line[1], set))
			ft_lstadd_back(&(scene->cameras), ft_lstnew(get_camera(ft_split_set(line, set))));
		else if (!ft_strncmp(line, "l", 1) && in_charset(line[1], set))
			ft_lstadd_back(&(scene->lights), ft_lstnew(get_light(ft_split_set(line, set))));
		else if (!ft_strncmp(line, "sp", 2) && in_charset(line[2], set))
			ft_lstadd_back(&(scene->spheres), ft_lstnew(get_sphere(ft_split_set(line, set))));
		else if (!ft_strncmp(line, "pl", 2) && in_charset(line[2], set))
			ft_lstadd_back(&(scene->planes), ft_lstnew(get_plane(ft_split_set(line, set))));
		else if (!ft_strncmp(line, "sq", 2) && in_charset(line[2], set))
			ft_lstadd_back(&(scene->squares), ft_lstnew(get_square(ft_split_set(line, set))));
		else if (!ft_strncmp(line, "cy", 2) && in_charset(line[2], set))
			ft_lstadd_back(&(scene->cylinders), ft_lstnew(get_cylinder(ft_split_set(line, set))));
		else if (!ft_strncmp(line, "tr", 2) && in_charset(line[2], set))
			ft_lstadd_back(&(scene->triangles), ft_lstnew(get_triangle(ft_split_set(line, set))));
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
