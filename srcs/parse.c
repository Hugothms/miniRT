/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 16:07:49 by hthomas          ###   ########.fr       */
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
	return(set_triple(tab[0], tab[1], tab[2]));
}

t_rgb		str_to_rgb(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return(set_rgb("tab[0]", "tab[1]", "tab[2]"));
}




















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













/*
** check if str is only made of char in charset
** @param str	string that will be checked
** @param set	set of chars
** @return		1 if there are only chars from charset in str, 0 otherwise
*/

int				is_from_charset(const char *str, const char *charset)
{
	int	i;
	int	j;
	int	ok;

	i = 0;
	while (str[i])
	{
		ok = 0;
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j++])
				ok = 1;
		}
		if (!ok)
			return (0);
		i++;
	}
	return (1);
}




t_scene			*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	*set;

	set = " \t";
	if(!(scene = malloc(sizeof(*scene))))
		return (NULL);
	while((ret = get_next_line(fd, &line)) == 1)
	{
		printf("\n|%s|\n", line);
		if(!ft_strncmp(line, "R", 1) && in_charset(line[1], set))
			scene->resolution = get_resolution(ft_split_set(line, set));
		else if(!ft_strncmp(line, "A", 1) && in_charset(line[1], set))
			scene->ambient_light = get_ambient_light(ft_split_set(line, set));
		else if(!ft_strncmp(line, "c", 1) && in_charset(line[1], set))
			ft_lstadd_back(&(scene->cameras), ft_lstnew(get_camera(ft_split_set(line, set))));
		else if(!ft_strncmp(line, "l", 1) && in_charset(line[1], set))
			ft_lstadd_back(&scene->lights, ft_lstnew(get_light(ft_split_set(line, set))));
		else if(!ft_strncmp(line, "sp", 2) && in_charset(line[2], set))
			ft_lstadd_back(&scene->spheres, ft_lstnew(get_sphere(ft_split_set(line, set))));
		else if(!ft_strncmp(line, "pl", 2) && in_charset(line[2], set))
			ft_lstadd_back(&scene->planes, ft_lstnew(get_plane(ft_split_set(line, set))));
		else if(!ft_strncmp(line, "sq", 2) && in_charset(line[2], set))
			ft_lstadd_back(&scene->squares, ft_lstnew(get_square(ft_split_set(line, set))));
		else if(!ft_strncmp(line, "cy", 2) && in_charset(line[2], set))
			ft_lstadd_back(&scene->cylinders, ft_lstnew(get_cylinder(ft_split_set(line, set))));
		else if(!ft_strncmp(line, "tr", 2) && in_charset(line[2], set))
			ft_lstadd_back(&scene->triangles, ft_lstnew(get_triangle(ft_split_set(line, set))));
		else if (!is_from_charset(line, set))
		{
			free(line);
			ft_putstr("Error\n");
			printf("ret: %d line = |%s|\n", ret, line);
			return (NULL);
		}
		free(line);
	}
	return (scene);
}
