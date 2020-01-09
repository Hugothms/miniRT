/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:51:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 11:45:21 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include"elements.h"

typedef struct		s_scene
{
	struct s_pixel			resolution;
	struct s_ambient_light	ambient_light;
	struct s_camera			*cameras;
	struct s_light			*lights;
	struct s_sphere			*spheres;
	struct s_plane			*planes;
	struct s_square			*squares;
	struct s_cylinder		*cylinders;
	struct s_triangle		*triangles;
}					t_scene;

#endif
