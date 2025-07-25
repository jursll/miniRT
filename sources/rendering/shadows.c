/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:25:13 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/25 15:07:09 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Check if point is in shadow */
int	is_in_shadow(t_rt *rt, t_v3d point, t_v3d light_pos)
{
	t_ray	shadow_ray;
	t_v3d	to_light;
	double	light_distance;
	double	t;
	int		i;

	/* Calculate direction and distance to light */
	to_light = vec_sub(light_pos, point);
	light_distance = vec_norm(to_light);

	/* Create shadow ray from surface point toward light
	   Small offset prevents self-shadowing */
	shadow_ray.origin = vec_add(point, sc_mult(normalize_vector(to_light), 0.0001));
	shadow_ray.direction = normalize_vector(to_light);

	/* Check if any sphere blocks the light */
	i = 0;
	while (i < rt->scene.num_spheres)
	{
		t = intersect_sphere(shadow_ray, rt->scene.spheres[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Sphere blocks light
		i++;
	}

	/* Check if any plane blocks the light */
	i = 0;
	while (i < rt->scene.num_planes)
	{
		t = intersect_plane(shadow_ray, rt->scene.planes[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Plane blocks light
		i++;
	}

	/* Check if any cylinder blocks the light */
	i = 0;
	while (i < rt->scene.num_cylinders)
	{
		t = intersect_cylinder(shadow_ray, rt->scene.cylinders[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Cylinder blocks light
		i++;
	}

	return (0);  // No shadow - light reaches the point
}
