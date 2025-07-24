/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scene_with_lights.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:18:26 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 15:18:49 by julrusse         ###   ########.fr       */
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
	rt->scene.lights[0].position = vec(-10, 10, -10);  // Upper left
	rt->scene.lights[0].brightness = 0.7;
	rt->scene.lights[0].color.r = 255;
	rt->scene.lights[0].color.g = 255;
	rt->scene.lights[0].color.b = 255;

	/* Three spheres */
	rt->scene.num_spheres = 3;
	rt->scene.spheres = malloc(sizeof(t_sphere) * 3);

	/* Red sphere (center) */
	rt->scene.spheres[0].center = vec(0, 0, 0);
	rt->scene.spheres[0].diameter = 4.0;
	rt->scene.spheres[0].color = (t_color){255, 0, 0};

	/* Green sphere (left) */
	rt->scene.spheres[1].center = vec(-5, 0, 0);
	rt->scene.spheres[1].diameter = 4.0;
	rt->scene.spheres[1].color = (t_color){0, 255, 0};

	/* Blue sphere (right) */
	rt->scene.spheres[2].center = vec(5, 0, 0);
	rt->scene.spheres[2].diameter = 4.0;
	rt->scene.spheres[2].color = (t_color){0, 0, 255};

	/* Add a floor plane */
	rt->scene.num_planes = 1;
	rt->scene.planes = malloc(sizeof(t_plane));
	rt->scene.planes[0].point = vec(0, -3, 0);     // 3 units down
	rt->scene.planes[0].normal = vec(0, 1, 0);     // Points up
	rt->scene.planes[0].color = (t_color){200, 200, 200};  // Light gray

	rt->scene.num_cylinders = 0;
}

/* What you should see:
   - Spheres with shading (bright on top-left, darker on bottom-right)
   - Gray floor plane
   - Smooth gradients showing 3D shape
   - Ambient lighting preventing pure black shadows */
