/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/19 18:53:35 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void        	ft_put_pixel(unsigned char *data, t_couple pixel, int color, int win_width)
{
	int	(*tab)[win_width][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.h][pixel.w] = color; // set the pixel at the coord x,y with the color value
}

/***
 * cree un ray depuis la posision de la camera qui passe par le pixel demandé
 * en prenant en compre la resolution de l'image et l'angle de vision de la camera
 ***/
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

/***
 * trouve l'objet le plus proche dans la direction du ray
 ***/
t_impact	*closest_object(const t_ray ray, const t_scene *scene, void **object)
{
	t_impact	*impact;

	if(!(impact = malloc(sizeof(*impact))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	impact->dist = INFINITY;
	//for each object in the scene
	ray_spheres(ray, scene, impact, object);
	// ray_planes(ray, scene, impact, object);
	// ray_squares(ray, scene, impact, object);
	// ray_cyinders(ray, scene, impact, object);
	// ray_triangles(ray, scene, impact, object);
	if (*object)
		return (impact);
	return (NULL);
}

t_rgb		*manage_light(const t_scene *scene, void *object, t_impact *impact, t_rgb *color)
{
	t_list		*lights;
	t_light		*light;
	t_ray		to_light;
	void		*obstacle;
	t_impact	*impact_light;

	lights = scene->lights;
	while (lights->next)
	{
		obstacle = NULL;
		light = (t_light*)(lights->content);
		to_light = new_ray(multi_vect(impact->pos, 1 - 1e-4), add_vect(light->pos, minus_vect(impact->pos)));
		impact_light = closest_object(to_light, scene, &obstacle); // rapprochement du point d'impact vers la camera
		// if(object == obstacle)
		// {
		// 	*color = *mult_rgb(light->color, *int_to_rgb(50,50,50));
		// 	return (NULL);
		// }
		//if the light is not in shadow of another object
		if (!obstacle)
		{
			//add this light contribution to computed color;
			*color = *mult_rgb(((t_sphere*)object)->color, light->color); // (a modifier)
		}
		//printf("%d,%d\n", pixel.w, pixel.h);
		lights = lights->next;
	}
	return (NULL);
}

void		print_img(const t_mlx *mlx,  t_img *img,const t_scene *scene)
{
	t_couple	pixel;
	t_rgb		*color;
	t_ray		ray;
	void		*object;
	float		reflec;
	int			depth;
	t_impact	*impact;

	pixel.h = -1;
	while (++pixel.h < scene->resolution.h)
	{
		pixel.w = -1;
		while (++pixel.w < scene->resolution.w)
		{
			color = int_to_rgb(0, 0, 0);
			reflec = REFLEC;
			depth = DEPTH;
			object = NULL; // peut etre a deplacer dans le while suivant
			impact = NULL; // idem
			while (depth-- && reflec > 1e-6)
			{
				ray = generate_ray(scene->cameras, scene->resolution, pixel);
				impact = closest_object(ray, scene, &object);
				//get_obj(scene->type, object);
				if (impact)
				{
					manage_light(scene, object, impact, color);
					//*color = ((t_sphere*)object)->color;
				}
				//Final color = Final color + computed color * previous reflection factor;
				//reflection factor = reflection factor * surface reflection property;
			}
			ft_put_pixel(img->data, pixel, rgb_to_int(*color), scene->resolution.w);
		}
	}
}



/*
2,5     -0.975546,-4.877731,16.718691   -0.026105,-0.184044,0.982571     17.443010
2,6     0.975546,-4.877731,16.718691    0.026105,-0.184044,0.982571      17.443010


3,4     -2.933097,-2.933097,16.755585   -0.078845,-0.132607,0.988028     17.261395
3,5     -0.915321,-2.745963,15.686564   -0.025417,-0.131787,0.990952     15.951377
3,6     0.915321,-2.745963,15.686564    0.025417,-0.131787,0.990952      15.951377
3,7     2.933097,-2.933097,16.755585    0.078845,-0.132607,0.988028      17.261395


4,4     -2.938599,-0.979533,16.787018   -0.079370,-0.080475,0.993592     17.070408
4,5     -0.919541,-0.919541,15.758881   -0.025621,-0.081348,0.996356     15.812447
4,6     0.919541,-0.919541,15.758881    0.025621,-0.081348,0.996356      15.812447
4,7     2.938599,-0.979533,16.787018    0.079370,-0.080475,0.993592      17.070408

5,3     -4.787921,0.957584,16.410862    -0.195500,0.088190,0.976730      17.121845
5,4     -2.759510,0.919837,15.763956    -0.144912,0.089541,0.985385      16.030075
5,5     -0.936448,0.936448,16.048632    -0.094514,0.089839,0.991462      16.103182
5,6     0.936448,0.936448,16.048632     0.094514,0.089839,0.991462       16.103182
5,7     2.759510,0.919837,15.763956     0.144912,0.089541,0.985385       16.030075
5,8     4.787921,0.957584,16.410862     0.195500,0.088190,0.976730       17.121845

6,3     -4.710021,2.826012,16.143854    -0.193740,0.138547,0.971221      17.052704
6,4     -2.722168,2.722168,15.550637    -0.143919,0.139233,0.979746      16.020073
6,5     -0.924167,2.772500,15.838159    -0.094171,0.140328,0.985616      16.105530
6,6     0.924167,2.772500,15.838159     0.094171,0.140328,0.985616       16.105530
6,7     2.722168,2.722168,15.550637     0.143919,0.139233,0.979746       16.020073
6,8     4.710021,2.826012,16.143854     0.193740,0.138547,0.971221       17.052704

7,4     -2.844419,4.740698,16.249002    -0.143217,0.189477,0.971384      17.163771
7,5     -0.970976,4.854882,16.640375    -0.092561,0.191601,0.977098      17.361301
7,6     0.970976,4.854882,16.640375     0.092561,0.191601,0.977098       17.361301
7,7     2.844419,4.740698,16.249002     0.143217,0.189477,0.971384       17.163771
la dist nest pas en fonction de la lumiere
*/























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
*/



/*
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




/*
Procedure RenderPicture()
  For each pixel on the screen,
    Generate a ray R from the viewing position through the point on the view
      plane corresponding to this pixel.
    Call the procedure RayTrace() with the arguments R and 0
    Plot the pixel in the colour value returned by RayTrace()
  Next pixel
End Procedure
Procedure RayTrace(ray R, integer Depth) returns colour
  Set the numerical variable Dis to a maximum value
  Set the object pointer Obj to null
  For each object in the scene
    Calculate the distance (from the starting point of R) of the nearest
      intersection of R with the object in the forward direction
    If this distance is less than Dis
      Update Dis to this distance
      Set Obj to point to this object
    End if
  Next object
  If Obj is not null
    Set the position variable Pt to the nearest intersection point of R and Obj
    Set the total colour C to black
    For each light source in the scene
      For each object in the scene
        If this object blocks the light coming from the light source to Pt
          Attenuate the intensity of the received light by the transmittivity
            of the object
        End if
      Next object
      Calculate the perceived colour of Obj at Pt due to this light source
        using the value of the attenuated light intensity
      Add this colour value to C
    Next light source
    If Depth is less than a maximum value
      Generate two rays Refl and Refr in the reflected and refracted directions,
        starting from Pt
      Call RayTrace with arguments Refl and Depth + 1
      Add (the return value * reflectivity of Obj) to C
      Call RayTrace with arguments Refr and Depth + 1
      Add (the return value * transmittivity of Obj) to C
    End if
  Else
    Set the total colour C to the background colour
  End if
  Return C
End Procedure
*/
