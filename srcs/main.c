/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 19:39:08 by hthomas          ###   ########.fr       */
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
		exit(0);
	}
	return (0);
}

void	print_img(void *mlx_ptr, void *win_ptr)
{
	t_rgb	rgb;
	int		x;
	int		y;
	int		color;

	rgb = ft_t_rgb(0120, 0120, 0120);
	color = ft_rgb(rgb);
	mlx_string_put(mlx_ptr, win_ptr, 100, 150, 01201201200, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 200, color, 			"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 250, 07770000000, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 300, 00007770000, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 350, 00000007770, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 400, 07770007770, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 450, 00007777770, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 500, 07777770000, 	"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 550, 07777777770, 	"Bonne Annee");
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

t_mlx 	*init_win_img(t_couple *resolution)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(*mlx))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(mlx->mlx_ptr = mlx_init()))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, resolution->x, resolution->y, "title window")))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	mlx_new_image(mlx->mlx_ptr, resolution->x, resolution->y);
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
	print_img(mlx->mlx_ptr, mlx->win_ptr);
	get_controls_loop(mlx);
	return (0);
}
