/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 15:20:26 by hthomas          ###   ########.fr       */
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

t_couple		get_resolution(char **strs)
{
	t_couple	res;

	res.x = ft_atoi(strs[1]);
	res.y = ft_atoi(strs[2]);
	return (res);
}

t_ambient_light	get_ambient_light(char **strs)
{
	t_ambient_light	res;
	char			**rgb;

	res.ratio = ft_atof(strs[1]);
	rgb = ft_split(strs[2], ',');
	res.rgb = set_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	res.z = ft_atof(strs[3]);
	return (res);
}

t_camera			*get_camera(char **strs)
{
	t_camera	res;

	res.pov = ;
	res. = ft_atoi(strs);
	return (res);
}

t_light			*get_light(char **strs)
{
	t_light	res;

	res. = ft_atoi(strs);
	res. = ft_atoi(strs);
	return (res);
}

t_plane			*get_plane(char **strs)
{
	t_plane	res;

	res. = ft_atoi(strs);
	res. = ft_atoi(strs);
	return (res);
}

t_sphere			*get_sphere(char **strs)
{
	t_sphere	res;

	res. = ft_atoi(strs);
	res. = ft_atoi(strs);
	return (res);
}

t_square			*get_square(char **strs)
{
	t_square	res;

	res. = ft_atoi(strs);
	res. = ft_atoi(strs);
	return (res);
}

	t_cylinder	res;
t_list			*get_cylinder(char **strs)
{
	t_cylinder	res;

	res. = ft_atoi(strs);
	res. = ft_atoi(strs);
	return (res);
}

t_list			*get_triangle(char **strs)
{
	t_list	res;

	res. = ft_atoi(strs);
	res. = ft_atoi(strs);
	return (res);
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
		else if(ft_strcmp(line, "pl") && in_charset(line[3], set))
			ft_lstadd_back(scene.planes, get_plane(ft_split_set(line, set)));
		else if(ft_strcmp(line, "sp") && in_charset(line[3], set))
			ft_lstadd_back(scene.spheres, get_sphere(ft_split_set(line, set)));
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
