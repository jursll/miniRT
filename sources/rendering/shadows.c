/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:25:13 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 15:25:50 by julrusse         ###   ########.fr       */
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

	/* Create ray from point to light */
	to_light = vec_sub(light_pos, point);
	light_distance = vec_norm(to_light);
	shadow_ray.origin = vec_add(point, sc_mult(to_light, 0.001)); // Small offset
	shadow_ray.direction = normalize_vector(to_light);

	/* Check if any object blocks the light */
	i = 0;
	while (i < rt->scene.num_spheres)
	{
		t = intersect_sphere(shadow_ray, rt->scene.spheres[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Object blocks light
		i++;
	}

	i = 0;
	while (i < rt->scene.num_planes)
	{
		t = intersect_plane(shadow_ray, rt->scene.planes[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Object blocks light
		i++;
	}

	return (0);  // No shadow
}

