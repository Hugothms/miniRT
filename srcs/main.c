/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/28 15:14:26 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		key_function(int keycode, t_mlx *mlx)
{
	printf("%i\n", keycode);
	if (keycode == 53)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		//free(mlx);
		exit(0);
	}
	else if (keycode == 123)
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	return (0);
}

t_scene	*get_scene(int argc, char *argv[])
{
	int			fd;
	t_scene		*scene;

	if (argc < 2 || argc > 3)
		print_err_and_exit("Wrong number of argument", 1);
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
		print_err_and_exit("2nd argument must be '--save'", 1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		print_err_and_exit(strerror(errno), errno);
	if (!(scene = parse(fd)))
		print_err_and_exit("Parsing error", PARSE_ERROR);
	if (close(fd) == -1)
		print_err_and_exit(strerror(errno), errno);
	return (scene);
}

t_mlx 	*init_win_img(t_couple resolution)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(*mlx))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(mlx->mlx_ptr = mlx_init()))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, resolution.w, resolution.h, "title window")))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, resolution.w, resolution.h)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (mlx);
}

void	get_controls_loop(t_mlx *mlx)
{
	mlx_key_hook(mlx->win_ptr, key_function, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int		main(int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;

	scene = get_scene(argc, argv);
	mlx = init_win_img(scene->resolution);
	print_img(mlx, scene);
	get_controls_loop(mlx);
	return (0);
}
