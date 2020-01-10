/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:15:02 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:19:21 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>

int		ft_function(int keycode, t_mlx *mlx)
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

void	ft_print(void *mlx_ptr, void *win_ptr)
{
	t_rgb	rgb;
	int		x;
	int		y;
	int		color;

	rgb = ft_t_rgb(0120, 0120, 0120);
	color = ft_rgb(rgb);
	mlx_string_put(mlx_ptr, win_ptr, 100, 150, 01201201200,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 200, color, 			"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 250, 07770000000,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 300, 00007770000,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 350, 00000007770,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 400, 07770007770,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 450, 00007777770,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 500, 07777770000,		"Bonne Annee");
	mlx_string_put(mlx_ptr, win_ptr, 100, 550, 07777777770,		"Bonne Annee");
}

int		main(int argc, char *argv[])
{
	int			fd;
	t_mlx		mlx;
	t_scene		*scene;

	if (argc < 2 || argc > 3)
		return (-1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (OPEN_ERROR);
	if (!(scene = parse(fd)))
		return (PARSE_ERROR);
	if (close(fd) == -1)
		return (CLOSE_ERROR);
	if (!(mlx.mlx_ptr = mlx_init()))
		return (-1);
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 1000, "title window")))
		return (-1);
	//mlx_new_image(mlx_ptr, int width, int height);
	ft_print(mlx.mlx_ptr, mlx.win_ptr);

	mlx_key_hook(mlx.win_ptr, ft_function, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
