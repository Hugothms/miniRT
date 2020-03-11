/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/11 12:43:37 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		*init_scene(t_scene *scene)
{
	scene->resolution.w = 0;
	scene->resolution.h = 0;
	scene->ambient_light.ratio = 0;
	scene->ambient_light.color.r = 0;
	scene->ambient_light.color.g = 0;
	scene->ambient_light.color.b = 0;
	scene->cameras = ft_lstnew(NULL);
	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->squares = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
	scene->triangles = ft_lstnew(NULL);
	if(!(scene->type = malloc(3 * sizeof(char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_bzero(scene->type, 3);
	return (scene);
}

t_scene		*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	*set;
	char	**data;

	set = " \t";
	if (!(scene = malloc(sizeof(*scene))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if(!(init_scene(scene)))
		return(NULL);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		data = ft_split_set((*line ? line : "iamcheating"), set);
		if (!ft_strcmp(data[0], "R") && ft_in_charset(line[1], set) && !scene->resolution.w)
			set_resolution(scene, data);
		else if (!ft_strcmp(data[0], "A") && ft_in_charset(line[1], set) && !scene->ambient_light.ratio)
			set_ambient_light(scene, data);
		else if (!ft_strcmp(data[0], "c") && ft_in_charset(line[1], set))
			set_camera(scene, data);
		else if (!ft_strcmp(data[0], "l") && ft_in_charset(line[1], set))
			set_light(scene, data);
		else if (!ft_strcmp(data[0], "sp") && ft_in_charset(line[2], set))
			set_sphere(scene, data);
		else if (!ft_strcmp(data[0], "pl") && ft_in_charset(line[2], set))
			set_plane(scene, data);
		else if (!ft_strcmp(data[0], "sq") && ft_in_charset(line[2], set))
			set_square(scene, data);
		else if (!ft_strcmp(data[0], "cy") && ft_in_charset(line[2], set))
			set_cylinder(scene, data);
		else if (!ft_strcmp(data[0], "tr") && ft_in_charset(line[2], set))
			set_triangle(scene, data);
		else if (!ft_is_from_charset(line, set))
		{
			free(line);
			free(data);
			ft_putstr("Error\n");
			return (NULL);
		}
		free(line);
		free(data);
	}
	return (scene);
}

t_scene		*get_scene(const int argc, const char *argv[])
{
	int			fd;
	t_scene		*scene;

	if (argc < 2 || argc > 3)
		print_err_and_exit("Wrong number of argument", 1);
	if (argc == 2 && ft_strncmp_rev(argv[1], ".rt", 3))
		print_err_and_exit("First argument must be a '.rt' file", 1);
	if (argc == 3 && ft_strcmp(argv[2], "-save"))
		print_err_and_exit("Second argument must be '-save'", 1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		print_err_and_exit(strerror(errno), errno);
	if (!(scene = parse(fd)))
		print_err_and_exit("Parsing error", PARSE_ERROR);
	if (close(fd) == -1)
		print_err_and_exit(strerror(errno), errno);
	return (scene);
}
