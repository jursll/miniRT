/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scene_with_lights.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:18:26 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/25 11:30:02 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Create a test scene with lighting */
void	create_lit_scene(t_rt *rt)
{
	/* Camera setup */
	rt->scene.camera.position = vec(0, 0, -20);
	rt->scene.camera.orientation = vec(0, 0, 1);
	rt->scene.camera.fov = 70;

	/* Ambient lighting (so nothing is completely black) */
	rt->scene.ambient.ratio = 0.2;  // 20% ambient light
	rt->scene.ambient.color.r = 255;
	rt->scene.ambient.color.g = 255;
	rt->scene.ambient.color.b = 255;

	/* Add a light source */
	rt->scene.num_lights = 1;
	rt->scene.lights = malloc(sizeof(t_light));
	rt->scene.lights[0].position = vec(0, 20, -10);
	rt->scene.lights[0].brightness = 0.7;
	rt->scene.lights[0].color.r = 255;
	rt->scene.lights[0].color.g = 255;
	rt->scene.lights[0].color.b = 255;

	/* Three spheres */
	rt->scene.num_spheres = 3;
	rt->scene.spheres = malloc(sizeof(t_sphere) * 3);

	/* Red sphere (center) */
	rt->scene.spheres[0].center = vec(0, 2, 0);
	rt->scene.spheres[0].diameter = 4.0;
	rt->scene.spheres[0].color = (t_color){255, 0, 0};

	/* Green sphere (left) */
	rt->scene.spheres[1].center = vec(-5, 2, 0);
	rt->scene.spheres[1].diameter = 4.0;
	rt->scene.spheres[1].color = (t_color){0, 255, 0};

	/* Add a cylinder */
	rt->scene.num_cylinders = 1;
	rt->scene.cylinders = malloc(sizeof(t_cylinder));
	rt->scene.cylinders[0].center = vec(5, 4, 0);
	rt->scene.cylinders[0].axis = vec(0, 1, 0);  // Vertical
	rt->scene.cylinders[0].diameter = 4.0;
	rt->scene.cylinders[0].height = 8.0;
	rt->scene.cylinders[0].color = (t_color){255, 128, 0};  // Orange

	/* Add a floor plane */
	rt->scene.num_planes = 1;
	rt->scene.planes = malloc(sizeof(t_plane));
	rt->scene.planes[0].point = vec(0, -3, 0);     // 3 units down
	rt->scene.planes[0].normal = vec(0, 1, 0);     // Points up
	rt->scene.planes[0].color = (t_color){200, 200, 200};  // Light gray

}


