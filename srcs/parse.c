/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/14 22:41:37 by hthomas          ###   ########.fr       */
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

int		is_good_size(char *line, char **data, int size, int nb_elements)
{
if (ft_in_charset(line[size], WHITE_SPACES))
		return (ft_tab_size(data) == nb_elements); 
}

t_scene		*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	**data;

	if (!(scene = malloc(sizeof(*scene))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if(!(init_scene(scene)))
		return(NULL);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		data = ft_split_set((*line ? line : "iamcheating"), WHITE_SPACES);
		if (!ft_strcmp(data[0], "R") && is_good_size(line, data, 1, 3) && !scene->resolution.w)
			set_resolution(scene, data);
		else if (!ft_strcmp(data[0], "A") && is_good_size(line, data, 1, 3) && !scene->ambient_light.ratio)
			set_ambient_light(scene, data);
		else if (!ft_strcmp(data[0], "c") && is_good_size(line, data, 1, 4))
			set_camera(scene, data);
		else if (!ft_strcmp(data[0], "l") && is_good_size(line, data, 1, 4))
			set_light(scene, data);
		else if (!ft_strcmp(data[0], "sp") && is_good_size(line, data, 2, 4))
			set_sphere(scene, data);
		else if (!ft_strcmp(data[0], "pl") && is_good_size(line, data, 2, 4))
			set_plane(scene, data);
		else if (!ft_strcmp(data[0], "sq") && is_good_size(line, data, 2, 5))
			set_square(scene, data);
		else if (!ft_strcmp(data[0], "cy") && is_good_size(line, data, 2, 6))
			set_cylinder(scene, data);
		else if (!ft_strcmp(data[0], "tr") && is_good_size(line, data, 2, 5))
			set_triangle(scene, data);
		else if (!ft_is_from_charset(line, WHITE_SPACES))
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
