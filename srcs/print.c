/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/28 18:45:17 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray generate_ray(const t_list *cameras, const t_couple resolution, t_couple pixel)
{
	t_vect vect_dir;

	//Ray = { starting point, direction };
	vect_dir = set_vect_dir_cam(((t_camera *)cameras->content), resolution, pixel.h, pixel.w);
	//printf("position:\t(% .3f,\t% .3f,\t% .3f)\n",\
											((t_camera*)cameras->content)->pos.x,\
											((t_camera*)cameras->content)->pos.y,\
											((t_camera*)cameras->content)->pos.z);
	//printf("direction:%s\t(% .3f,\t% .3f,\t % .3f)\n\n",\
											i  == resolution.h / 2 \
											&& pixel.w == resolution.w / 2 ? "\tmiddle\n\n" : "",\
											vect_dir.x,\
											vect_dir.y,\
											vect_dir.z);
	return (new_ray(((t_camera *)(cameras))->pos, vect_dir));
}

void 	*trace_ray(const t_ray ray, const t_scene *scene, float dist)
{
	t_list		*spheres;

	spheres = scene->spheres;
	//for each object in the scene
	while(spheres)
	{
		//determine closest ray/object intersection;
		if (intersect_sphere(ray, *(t_sphere*)(scene->spheres->content)) < dist)
			return ((t_sphere*)(scene->spheres->content));
		spheres = spheres->next;
	}
	return (0);
}

void	print_img(const t_mlx *mlx, const t_scene *scene)
{
	t_couple	pixel;
	int			color;
	t_ray		ray;
	void		*object;
	float		reflection_factor;
	int			depth;
	float		dist;

	pixel.h = -1;
	while (++pixel.h < scene->resolution.h)
	{
		pixel.w = -1;
		while (++pixel.w < scene->resolution.w)
		{
			//Final color = 0;
			color = rgb_to_int(float_to_rgb(0, 0, 0));
			reflection_factor = 1;
			//Repeat until reflection factor is 0 or maximum depth is reached;
			depth = 1;
			object = NULL;
			while(reflection_factor > 1e-6 && depth--)
			{
				dist = INFINITY;
				ray = generate_ray(scene->cameras, scene->resolution, pixel);
				object = trace_ray(ray, scene, dist);
				//if intersection exists
				t_sphere sphere = *(t_sphere *)(scene->spheres->content);
				if (object)
				{
					//for each light in the scene
					{
						//if the light is not in shadow of another object
						{
							//add this light contribution to computed color;
						}
					}
					color = (rgb_to_int(sphere.color));
				}
				//Final color = Final color + computed color * previous reflection factor;
				//reflection factor = reflection factor * surface reflection property;
			}
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel.w, pixel.h, color);
		}
	}
}

/*
		// compute primary ray direction
		Ray primRay;
		computePrimRay(i, j, &primRay);
		// shoot prim ray in the scene and search for intersection
		Point pHit;
		Normal nHit;
		float minDist = INFINITY;
		Object object = NULL;
		for (int k = 0; k < objects.size(); ++k)
		{
			if (Intersect(objects[k], primRay, &pHit, &nHit))
			{
				float distance = Distance(eyePosition, pHit);
				if (distance < minDistance)
				{
					object = objects[k];
					minDistance = distance; // update min distance
				}
			}
		}
		if (object != NULL)
		{
			// compute illumination
			Ray shadowRay;
			shadowRay.direction = lightPosition - pHit;
			bool isShadow = false;
			for (int k = 0; k < objects.size(); ++k)
			{
				if (Intersect(objects[k], shadowRay))
				{
					isInShadow = true;
					break;
				}
			}
		}
		if (!isInShadow)
			pixels[i][j] = object->color * light.brightness;
		else
			pixels[i][j] = 0;


for each pixel do
	compute viewing ray
	set pixel color to background color
	if (ray hits an object with t ∈ [0,∞)) then
		Compute n
		Evaluate lighting equation and set pixel to that color

Here the statement “if ray hits an object...” can be implemented as a function that tests for hits in the interval t ∈ [t0, t1]:
	hit = false
	for each object o do
		if (object is hit at ray parameter t and t ∈ [t0, t1]) then
			hit = true
			hitobject = o
			t1 = t
	return hit
*/





