/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/21 19:20:29 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		key_function(int keycode, t_window *w)
{
	printf("%i\n", keycode);
	if (keycode == 53)
	{
		mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
		mlx_destroy_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
		//free(mlx);
		exit(0);
	}
	else if (keycode == 123)
	{
		mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
		mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->img1->img_ptr, 0, 0);
	}
	else if (keycode == 124)
	{
		mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
		//mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->img2->img_ptr, 0, 0);
	}
	if (keycode == 1)
		save_bmp(screenshot_datetime(), w->img1->data, w->scene->resolution);
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

t_img	*init_img(t_mlx *mlx, t_couple resolution)
{
	t_img		*img;

	if (!(img = malloc(sizeof(*img))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(img->img_ptr = mlx_new_image(mlx->mlx_ptr, resolution.w, resolution.h)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(img->data = (unsigned char*)mlx_get_data_addr(img->img_ptr, &(img->bits_per_pixel), &(img->size_line), &(img->endian))))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (img);
}

void	get_controls_loop(t_mlx *mlx, t_img *img, t_scene *scene)
{
	t_window	*window;

	//mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	if(!(window = malloc(sizeof(*window))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	window->mlx = mlx;
	window->img1 = img;
	window->img2 = img;
	window->scene = scene;
	mlx_key_hook(mlx->win_ptr, key_function, window);
	mlx_loop(mlx->mlx_ptr);
}

int		main(int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_img		*img;

	clock_t start, end;
	start = clock();
	scene = get_scene(argc, argv);
	end = clock();
	printf("\nget_scene:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	start = clock();
	mlx = malloc_mlx_init();
	end = clock();
	printf("malloc_mlx_init:%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	start = clock();
	img = init_img(mlx, scene->resolution);
	end = clock();
	printf("init_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	start = clock();
	make_img(img, scene);
	end = clock();
	printf("make_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	if (argc == 2)
	{
		if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, scene->resolution.w, scene->resolution.h, "title window")))
		print_err_and_exit("Minilibx error", MLX_ERROR);
		start = clock();
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
		end = clock();
		printf("put_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
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
