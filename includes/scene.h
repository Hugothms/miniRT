/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:51:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/04/15 13:18:39 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct		s_scene
{
	t_couple		resolution;
	t_ambient_light	amb_light;
	t_list			*cameras;
	t_list			*lights;
	t_list			*spheres;
	t_list			*planes;
	t_list			*squares;
	t_list			*cylinders;
	t_list			*triangles;
	char			*type;
}					t_scene;

#endif
