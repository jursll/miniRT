/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:25:13 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:56:43 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_shadow_ray(t_ray *ray, t_v3d point, t_v3d light_pos,
			double *light_distance)
{
	t_v3d	to_light;

	to_light = vec_sub(light_pos, point);
	*light_distance = vec_norm(to_light);
	to_light = normalize_vector(to_light);
	ray->origin = vec_add(point, sc_mult(to_light, 0.0001));
	ray->direction = to_light;
}

int	check_sphere_shadow(t_rt *rt, t_ray ray, double max_dist)
{
	int		i;
	double	t;

	i = 0;
	while (i < rt->scene.num_spheres)
	{
		t = intersect_sphere(ray, rt->scene.spheres[i]);
		if (t > 0 && t < max_dist)
			return (1);
		i++;
	}
	return (0);
}

int	check_cylinder_shadow(t_rt *rt, t_ray ray, double max_dist)
{
	int		i;
	double	t;

	i = 0;
	while (i < rt->scene.num_cylinders)
	{
		t = intersect_cylinder(ray, rt->scene.cylinders[i]);
		if (t > 0 && t < max_dist)
			return (1);
		i++;
	}
	return (0);
}

int	check_plane_shadow(t_rt *rt, t_ray ray, double max_dist)
{
	int		i;
	double	t;

	i = 0;
	while (i < rt->scene.num_planes)
	{
		t = intersect_plane(ray, rt->scene.planes[i]);
		if (t > 0 && t < max_dist)
			return (1);
		i++;
	}
	return (0);
}

int	is_in_shadow(t_rt *rt, t_v3d point, t_v3d light_pos)
{
	t_ray	shadow_ray;
	double	light_distance;

	init_shadow_ray(&shadow_ray, point, light_pos, &light_distance);
	if (check_sphere_shadow(rt, shadow_ray, light_distance))
		return (1);
	if (check_cylinder_shadow(rt, shadow_ray, light_distance))
		return (1);
	if (check_plane_shadow(rt, shadow_ray, light_distance))
		return (1);
	return (0);
}
