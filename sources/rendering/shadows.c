/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:25:13 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 16:46:26 by julrusse         ###   ########.fr       */
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

	to_light = vec_sub(light_pos, point);
	light_distance = vec_norm(to_light);

	// Small optimization: normalize once
	to_light = normalize_vector(to_light);
	shadow_ray.origin = vec_add(point, sc_mult(to_light, 0.0001));
	shadow_ray.direction = to_light;

	// Check spheres first (usually fewer and faster)
	i = -1;
	while (++i < rt->scene.num_spheres)
	{
		t = intersect_sphere(shadow_ray, rt->scene.spheres[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Early exit
	}

	// Then check cylinders
	i = -1;
	while (++i < rt->scene.num_cylinders)
	{
		t = intersect_cylinder(shadow_ray, rt->scene.cylinders[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Early exit
	}

	// Finally check planes (often infinite, so check last)
	i = -1;
	while (++i < rt->scene.num_planes)
	{
		t = intersect_plane(shadow_ray, rt->scene.planes[i]);
		if (t > 0 && t < light_distance)
			return (1);  // Early exit
	}

	return (0);
}
