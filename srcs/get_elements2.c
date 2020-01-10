/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:53:11 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 17:18:31 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include<stdio.h>

t_sphere		*get_sphere(char **strs)
{
	t_sphere	*sphere;

	printf("get sphere\n");
	if (!(sphere = malloc(sizeof(*sphere))))
		return (NULL);
	sphere->pos = str_to_triple(strs[1]);
	sphere->diameter = ft_atof(strs[2]);
	sphere->color = str_to_rgb(strs[3]);
	return (sphere);
}

t_plane			*get_plane(char **strs)
{
	t_plane		*plane;

	printf("get plane\n");
	if (!(plane = malloc(sizeof(*plane))))
		return (NULL);
	plane->pos = str_to_triple(strs[1]);
	plane->vect = str_to_triple(strs[2]);
	plane->color = str_to_rgb(strs[3]);
	return (plane);
}

t_square		*get_square(char **strs)
{
	t_square	*square;

	printf("get square\n");
	if (!(square = malloc(sizeof(*square))))
		return (NULL);
	square->pos = str_to_triple(strs[1]);
	square->vect = str_to_triple(strs[2]);
	square->height = ft_atof(strs[3]);
	square->color = str_to_rgb(strs[4]);
	return (square);
}

t_cylinder		*get_cylinder(char **strs)
{
	t_cylinder	*cylinder;

	printf("get cylinder\n");
	if (!(cylinder = malloc(sizeof(*cylinder))))
		return (NULL);
	cylinder->pos = str_to_triple(strs[1]);
	cylinder->vect = str_to_triple(strs[2]);
	cylinder->diameter = ft_atof(strs[3]);
	cylinder->height = ft_atof(strs[4]);
	cylinder->color = str_to_rgb(strs[5]);
	return (cylinder);
}

t_triangle		*get_triangle(char **strs)
{
	t_triangle	*triangle;

	printf("get triangle\n");
	if (!(triangle = malloc(sizeof(*triangle))))
		return (NULL);
	triangle->p1 = str_to_triple(strs[1]);
	triangle->p2 = str_to_triple(strs[2]);
	triangle->p3 = str_to_triple(strs[3]);
	triangle->color = str_to_rgb(strs[4]);
	return (triangle);
}
