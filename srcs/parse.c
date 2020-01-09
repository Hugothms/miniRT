/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 13:51:52 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_couple		get_resolution(char *str)
{

}

t_ambient_light	get_ambient_light(char *str)
{

}

t_list			get_camera(char *str)
{

}

t_list			get_light(char *str)
{

}

t_list			get_plane(char *str)
{

}

t_list			get_sphere(char *str)
{

}

t_list			get_square(char *str)
{

}

t_list			get_cylinder(char *str)
{

}

t_list			get_triangle(char *str)
{

}

t_scene			parse(int fd)
{
	t_scene	scene;
	char	*line;
	int		ret;

	while((ret = get_next_line(fd, &line)) == 1)
	{
		printf("\nret: %d line = |%s|\n", ret, line);
		if(line[0] == 'R' && (line[1] == ' ' || line[1] == '\t'))
			scene.resolution = get_resolution(line);
		if(line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
			scene.ambient_light = get_ambient_light(line);
		if(line[0] == 'c' && (line[1] == ' ' || line[1] == '\t'))
			scene.cameras = get_camera(line);
		if(line[0] == 'l' && (line[1] == ' ' || line[1] == '\t'))
			scene.lights = get_light(line);
		if(line[0] == 'p' && line[1] == 'l' && (line[2] == ' ' || line[2] == '\t'))
			scene.planes = get_plane(line);
		if(line[0] == 's' && line[1] == 'p' && (line[2] == ' ' || line[2] == '\t'))
			scene.spheres = get_sphere(line);
		if(line[0] == 's' && line[1] == 'q' && (line[2] == ' ' || line[2] == '\t'))
			scene.squares = get_square(line);
		if(line[0] == 'c' && line[1] == 'y' && (line[2] == ' ' || line[2] == '\t'))
			scene.cylinders = get_cylinder(line);
		if(line[0] == 't' && line[1] == 'r' && (line[2] == ' ' || line[2] == '\t'))
			scene.triangles = get_triangle(line);
		free(line);
	}
	return (scene);
}
