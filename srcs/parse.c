/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/15 14:17:21 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		*init_scene(t_scene *scene)
{
	scene->resolution.w = 0;
	scene->resolution.h = 0;
	scene->amb_light.ratio = 0;
	scene->amb_light.color.r = 0;
	scene->amb_light.color.g = 0;
	scene->amb_light.color.b = 0;
	scene->cameras = ft_lstnew(NULL);
	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->squares = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
	scene->triangles = ft_lstnew(NULL);
	if (!(scene->type = malloc(3 * sizeof(char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_bzero(scene->type, 3);
	return (scene);
}

int		check_line(char *line, char **data, char *type, int nb_elements)
{
	if (!ft_strcmp(data[0],type))
	{
		if (ft_in_charset(line[ft_strlen(type)], WHITE_SPACES))
			return (ft_tab_size(data) == nb_elements);
	}
	return (0);
}

t_scene		*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	**data;

	if (!(scene = malloc(sizeof(*scene))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(init_scene(scene)))
		return (NULL);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		data = ft_split_set((*line ? line : "iamcheating"), WHITE_SPACES);
		if (check_line(line, data, "R", 3) && !scene->resolution.w)
			set_resolution(scene, data);
		else if (check_line(line, data, "A", 3) && !scene->amb_light.ratio)
			set_ambient_light(scene, data);
		else if (check_line(line, data, "c", 4))
			set_camera(scene, data);
		else if (check_line(line, data, "l", 4))
			set_light(scene, data);
		else if (check_line(line, data, "sp", 4))
			set_sphere(scene, data);
		else if (check_line(line, data, "pl", 4))
			set_plane(scene, data);
		else if (check_line(line, data, "sq", 5))
			set_square(scene, data);
		else if (check_line(line, data, "cy", 6))
			set_cylinder(scene, data);
		else if (check_line(line, data, "tr", 5))
			set_triangle(scene, data);
		else if (!ft_is_from_charset(line, WHITE_SPACES))
		{
			free(line);
			free(data);
			print_err_and_exit("Parse error", PARSE_ERROR);
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
