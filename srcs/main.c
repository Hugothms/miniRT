/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/04 17:44:07 by hthomas          ###   ########.fr       */
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

t_mlx	*init_win(t_couple resolution)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(*mlx))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(mlx->mlx_ptr = mlx_init()))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, resolution.w, resolution.h, "title window")))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (mlx);
}

t_img	*init_img(t_mlx *mlx, t_couple resolution)
{
	t_img		*img;

	if (!(img = malloc(sizeof(*img))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(img->img_ptr = mlx_new_image(mlx->mlx_ptr, resolution.w, resolution.h)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(img->data = (unsigned char*)mlx_get_data_addr(img->img_ptr, &(img->bits_per_pixel), &(img->size_line), &(img->endian))))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	printf("%d'%d'%d\n",(img->bits_per_pixel), (img->size_line), (img->endian));
	return (img);
}

void	get_controls_loop(t_mlx *mlx, t_img *img)
{
	(void)img;
	mlx_key_hook(mlx->win_ptr, key_function, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int		main(int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_img		*img;

	scene = get_scene(argc, argv);
	mlx = init_win(scene->resolution);
	img = init_img(mlx, scene->resolution);
	print_img(mlx, img, scene);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
	if (argc == 3)
		save_img(screenshot_datetime(), img->data, scene->resolution);
	get_controls_loop(mlx, img);
	return (0);
}
