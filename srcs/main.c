/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 12:00:44 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>

t_rgb	ft_t_rgb(int r, int g, int b)
{
	t_rgb	rgb;

 	rgb.r =  r;
 	rgb.g =  g;
 	rgb.b =  b;
	return (rgb);
}

int		ft_rgb(t_rgb rgb)
{
	int	color;

	color = 0;
 	color += 2097152 * rgb.r;
 	color += 4096 * rgb.g;
 	color += 8 * rgb.b;
	return (color);
}

int	ft_function(int keycode, t_mlx *mlx)
{
	printf("%i\n", keycode);
	if(keycode == 53)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_window (mlx->mlx_ptr, mlx->win_ptr);
		exit (0);
	}
	return (0);
}

void 	ft_print(void *mlx_ptr, void *win_ptr)
{
	t_rgb	rgb;
	int		x;
	int		y;
	int		color;

	rgb = ft_t_rgb(0120, 0120, 0120);
	color = ft_rgb(rgb);

	mlx_string_put(mlx_ptr,win_ptr, 100, 150, 01201201200,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 200, color,			"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 250, 07770000000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 300, 00007770000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 350, 00000007770,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 400, 07770007770,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 450, 00007777770,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 500, 07777770000,		"Bonne Annee" );
	mlx_string_put(mlx_ptr,win_ptr, 100, 550, 07777777770,		"Bonne Annee" );
}

t_scene	parse(int fd)
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
			scene.cameras = get_cameras(line);
		if(line[0] == 'l' && (line[1] == ' ' || line[1] == '\t'))
			scene.lights = get_lights(line);
		if(line[0] == 'p' && line[1] == 'l' && (line[2] == ' ' || line[2] == '\t'))
			scene.planes = get_planes(line);
		if(line[0] == 's' && line[1] == 'p' && (line[2] == ' ' || line[2] == '\t'))
			scene.spheres = get_spheres(line);
		if(line[0] == 's' && line[1] == 'q' && (line[2] == ' ' || line[2] == '\t'))
			scene.squares = get_squares(line);
		if(line[0] == 'c' && line[1] == 'y' && (line[2] == ' ' || line[2] == '\t'))
			scene.cylinders = get_cylinders(line);
		if(line[0] == 't' && line[1] == 'r' && (line[2] == ' ' || line[2] == '\t'))
			scene.triangles = get_triangles(line);
		free(line);
	}
	return (scene);
}

int 	main(int argc, char *argv[])
{
	int			fd;
	t_mlx		mlx;
	t_scene		scene;

	if(argc < 2 || argc > 3)
		return (-1);



	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (OPEN_ERROR);
	// if(!(scene = parse(fd)))
	// 	return (PARSE_ERROR);
	parse(fd);
	if (close(fd) == -1)
		return (CLOSE_ERROR);



	if(!(mlx.mlx_ptr = mlx_init()))
		return (-1);
	if(!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 1000, "title window")))
		return (-1);

	//mlx_new_image(mlx_ptr, int width, int height);
	ft_print(mlx.mlx_ptr, mlx.win_ptr);

	mlx_key_hook(mlx.win_ptr, ft_function, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
