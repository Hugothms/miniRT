/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/26 12:20:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	close_function(const t_window *w)
{
	mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	mlx_destroy_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	//free(mlx);
	exit(0);
}

int	key_function(const int keycode, const t_window *w)
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

void 	make_img_multi_thread(t_img *img, t_scene *scene, const t_camera *camera)
{
	t_couple	start;
	float		step;
	size_t		i;

	start.w = 0;
	start.h = 0;
	step = scene->resolution.h / (float) (THREADS);
	// if (step < 1)
	// 	step = 1;
	int	fd[THREADS][2];
	for (i = 0; i < THREADS - 1; i++)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("Pipe failed\n", STDERR);
			exit(PIPE_ERROR);
		}
		printf("Pipe %zu is %d,%d\n", i, fd[i][0], fd[i][1]);
		printf("Will fork %zu\n", i);
		int pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Fork failed\n", STDERR);
			exit(FORK_ERROR);
		}
		if (pid == 0)
		{
			close(fd[i][0]);
			start.h = i * step;
			scene->resolution.h = ft_max_int(0, (i + 1) * step - 1);
			if (start.h > scene->resolution.h)
				exit(0);
			// printf("\nmake_img %zu from %.1f\t %.1f\n", i, 	i * step, 	(i + 1) * step - 1);
			printf("make_img%zu from %i to %i\n", 		i, 	start.h,	scene->resolution.h);
			make_img(img->data, scene, camera, start);
			printf("Process %zu will write in %i at offset %i for %i bytes\n", i, fd[i][1], start.h * img->size_line, (scene->resolution.h - start.h) * img->size_line);
			write(fd[i][1], ((void*)(img->data)) + start.h * img->size_line, (scene->resolution.h - start.h) * img->size_line);
			printf("Process %zu wrode\n", i);
			close(fd[i][1]);
			exit(0);
		}
	}
	start.h = i * step;
	scene->resolution.h = ft_max_int(0, (i + 1) * step);
	// printf("\nmake_img %zu from %.1f\t %.1f\n", i, 	i * step, 	(i + 1) * step);
	printf("make_img%zu from %i to %i\n", i, start.h, scene->resolution.h);
	make_img(img->data, scene, camera, start);
	while (wait(NULL) > 0)
		;
	printf("end waiting\n");
	for (i = 0; i < THREADS - 1; i++)
	{
		start.h = i * step;
		scene->resolution.h = ft_max_int(0, (i + 1) * step - 1);
		close(fd[i][1]);
		// wait(NULL);
		printf("for loop %zu will read in %i at offset %i for %i bytes\n", i, fd[i][0], start.h * img->size_line, (scene->resolution.h - start.h) * img->size_line);
		read(fd[i][0], ((void*)(img->data)) + start.h * img->size_line, (scene->resolution.h - start.h) * img->size_line);
		printf("for loop %zu rode\n", i);
		close(fd[i][0]);
	}
}

int	main(const int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_img		*img;

	clock_t start, end;
	start = clock();
	scene = get_scene(argc, argv);
	mlx = malloc_mlx_init();
	img = init_img(mlx, &scene->resolution);
	make_img_multi_thread(img, scene, scene->cameras->content);
	// make_img(img, scene, scene->cameras->content);
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
