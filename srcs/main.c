/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/25 20:34:33 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		close_function(const t_window *w)
{
	mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	mlx_destroy_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	//free(mlx);
	exit(0);
}

int		key_function(const int keycode, const t_window *w)
{
	clock_t start, end;
	printf("%i\n", keycode);
	if (keycode == ESC || keycode == KEY_Q)
		close_function(w);
	else if (keycode == LEFT)
	{
		mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
		mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->img->img_ptr, 0, 0);
	}
	else if (keycode == RIGHT)
	{
		mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
		//mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->img2->img_ptr, 0, 0);
	}
	if (keycode == KEY_S)
	{
		start = clock();
		save_bmp(screenshot_datetime(), w->img->data, w->scene->resolution);
		end = clock();
		printf("save_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	}
	return (0);
}

t_mlx	*malloc_mlx_init(void)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(*mlx))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(mlx->mlx_ptr = mlx_init()))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (mlx);
}

t_img	*init_img(t_mlx *mlx, t_couple *resolution)
{
	t_img		*img;
	int			w;
	int			h;

	if (!(img = malloc(sizeof(*img))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	w = 1080;
	h = 720;
	// mlx_get_screen_size(mlx->mlx_ptr, &w, &h);
	// if (w < resolution->w)
	// 	resolution->w = w;
	// if (h < resolution->h)
	// 	resolution->h = h;
	if (!(img->img_ptr = mlx_new_image(mlx->mlx_ptr, resolution->w, resolution->h)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(img->data = (unsigned char*)mlx_get_data_addr(img->img_ptr, &(img->bits_per_pixel), &(img->size_line), &(img->endian))))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (img);
}

void	get_controls_loop(t_mlx *mlx, t_img *img, t_scene *scene)
{
	t_window	*window;

	if(!(window = malloc(sizeof(*window))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	window->mlx = mlx;
	window->img = img;
	window->scene = scene;
	mlx_hook(mlx->win_ptr, 17, 1L<<17, close_function, window);
	mlx_key_hook(mlx->win_ptr, key_function, window);
	mlx_loop(mlx->mlx_ptr);
}

int		main(const int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_img		*img;

	clock_t start, end;
	start = clock();
	scene = get_scene(argc, argv);
	mlx = malloc_mlx_init();
	img = init_img(mlx, &scene->resolution);
	make_img(img, scene, scene->cameras->content);
	end = clock();
	printf("make_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	if (argc == 2)
	{
		char *title_window = ft_strjoin("miniRT - ", argv[1]);
		if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, scene->resolution.w, scene->resolution.h, title_window)))
			print_err_and_exit("Minilibx error", MLX_ERROR);
		free(title_window);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
		get_controls_loop(mlx, img, scene);
	}
	else if (argc == 3)
	{
		start = clock();
		save_bmp(screenshot_datetime(), img->data, scene->resolution);
		end = clock();
		printf("save_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	}
	return (0);
}
