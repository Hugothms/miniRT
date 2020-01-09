/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 16:40:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_triple		set_triple(float x, float y, float z)
{
	t_triple	triple;

	triple.x = ft_atof(x);
	triple.y = ft_atof(y);
	triple.z = ft_atof(z);
	retrun (triple);
}

t_triple		str_to_triple(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return(set_triple(ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2])));
}

t_rgb		str_to_rgb(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return(set_rgb(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2])));
}




















t_couple		get_resolution(char **strs)
{
	t_couple	resolution;

	resolution.x = ft_atoi(strs[1]);
	resolution.y = ft_atoi(strs[2]);
	return (resolution);
}

t_ambient_light	get_ambient_light(char **strs)
{
	t_ambient_light	ambiant_light;

	ambiant_light.ratio = ft_atof(strs[1]);
	ambiant_light.rgb = str_to_rgb(strs[2]);
	ambiant_light.z = ft_atof(strs[3]);
	return (ambiant_light);
}








t_camera		*get_camera(char **strs)
{
	t_camera	*camera;

	if(!(camera = malloc(sizeof(*camera))))
		return (NULL);
	camera->pov = str_to_triple(strs[1]);
	camera->orientation = str_to_triple(strs[2]);
	camera->fov = ft_atof(strs[3]);
	return (camera);
}

t_light			*get_light(char **strs)
{
	t_light		*light;

	if(!(light = malloc(sizeof(*light))))
		return (NULL);
	light->pos = str_to_triple(strs[1]);
	light->ratio = ft_atof(strs[2]);
	light->color = str_to_rgb(strs[3]);
	return (light);
}

t_sphere		*get_sphere(char **strs)
{
	t_sphere	*sphere;

	if(!(sphere = malloc(sizeof(*sphere))))
		return (NULL);
	sphere->pos = str_to_triple(strs[1]);
	sphere->diameter = ft_atof(strs[2]);
	sphere->color = str_to_rgb(strs[3]);
	return (sphere);
}

t_plane			*get_plane(char **strs)
{
	t_plane		*plane;

	if(!(plane = malloc(sizeof(*plane))))
		return (NULL);
	plane->pos = str_to_triple(strs[1]);
	plane->vect = str_to_triple(strs[2]);
	plane->color = str_to_rgb(strs[3]);
	return (plane);
}

t_square		*get_square(char **strs)
{
	t_square	*square;

	if(!(square = malloc(sizeof(*square))))
		return (NULL);
	square->pos = str_to_triple(strs[1]);
	square->vect = str_to_triple(strs[2]);
	square->height = ft_atof(strs[3]);
	square->color = str_to_rgb(strs[4]);
	return (square);
}

t_cylinder		*get_cylinder(char **strs)
{
	t_cylinder	*cylinder;

	if(!(cylinder = malloc(sizeof(*cylinder))))
		return (NULL);
	cylinder->pos = str_to_triple(strs[1]);
	cylinder->vect = str_to_triple(strs[2]);
	cylinder->diameter = ft_atof(strs[3]);
	cylinder->height = ft_atof(strs[4]);
	cylinder->color = str_to_rgb(strs[5]);
	return (cylinder);
}

t_triangle		*get_triangle(char **strs)
{
	t_triangle	*triangle;

	if(!(triangle = malloc(sizeof(*triangle))))
		return (NULL);
	triangle->p1 = str_to_triple(strs[1]);
	triangle->p2 = str_to_triple(strs[2]);
	triangle->p3 = str_to_triple(strs[3]);
	triangle->color = str_to_rgb(strs[4]);
	return (triangle);
}




















t_scene			parse(int fd)
{
	t_scene	scene;
	char	*line;
	int		ret;
	char	*set;

	set = " \t";
	while((ret = get_next_line(fd, &line)) == 1)
	{
		printf("\nret: %d line = |%s|\n", ret, line);

		if(ft_strcmp(line, "R" && in_charset(line[2], set)))
			scene.resolution = get_resolution(ft_split_set(line, set));
		else if(ft_strcmp(line, "A" && in_charset(line[2], set)))
			scene.ambient_light = get_ambient_light(ft_split_set(line, set));
		else if(ft_strcmp(line, "c" && in_charset(line[2], set)))
			ft_lstadd_back(scene.cameras, get_camera(ft_split_set(line, set)));
		else if(ft_strcmp(line, "l" && in_charset(line[2], set)))
			ft_lstadd_back(scene.lights, get_light(ft_split_set(line, set)));
		else if(ft_strcmp(line, "sp") && in_charset(line[3], set))
			ft_lstadd_back(scene.spheres, get_sphere(ft_split_set(line, set)));
		else if(ft_strcmp(line, "pl") && in_charset(line[3], set))
			ft_lstadd_back(scene.planes, get_plane(ft_split_set(line, set)));
		else if(ft_strcmp(line, "sq") && in_charset(line[3], set))
			ft_lstadd_back(scene.squares, get_square(ft_split_set(line, set)));
		else if(ft_strcmp(line, "cy") && in_charset(line[3], set))
			ft_lstadd_back(scene.cylinders, get_cylinder(ft_split_set(line, set)));
		else if(ft_strcmp(line, "tr") && in_charset(line[3], set))
			ft_lstadd_back(scene.triangles, get_triangle(ft_split_set(line, set)));
		else if (!ft_split_set(line, set))
			retrun (NULL);
		free(line);
	}
	return (scene);
}
