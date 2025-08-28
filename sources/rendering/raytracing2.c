/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:21:38 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:56:35 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_color	calculate_lighting(t_rt *rt, t_hit *hit)
{
	t_color	final_color;
	t_color	ambient;

	ambient = apply_ambient(hit->color, rt->scene.ambient);
	final_color = ambient;
	final_color = apply_all_lights(rt, hit, final_color);
	return (final_color);
}

t_color	apply_all_lights(t_rt *rt, t_hit *hit, t_color base_color)
{
	t_color	result;
	int		i;

	result = base_color;
	i = 0;
	while (i < rt->scene.num_lights)
	{
		result = apply_light_contribution(rt, hit, result, i);
		i++;
	}
	return (result);
}

t_color	apply_light_contribution(t_rt *rt, t_hit *hit, t_color current, int i)
{
	t_color	diffuse;
	t_v3d	light_dir;
	double	intensity;

	light_dir = vec_sub(rt->scene.lights[i].position, hit->point);
	light_dir = normalize_vector(light_dir);
	intensity = vec_dot(hit->normal, light_dir);
	if (intensity <= 0)
		return (current);
	if (is_in_shadow(rt, hit->point, rt->scene.lights[i].position))
		return (current);
	intensity *= rt->scene.lights[i].brightness;
	diffuse = calculate_diffuse(hit->color, hit->normal, light_dir, intensity);
	return (add_colors(current, diffuse));
}

int	trace_ray(t_rt *rt, t_ray ray)
{
	t_hit	hit;
	int		i;
	t_color	lit_color;

	hit.t = INFINITY;
	hit.hit_anything = 0;
	i = 0;
	while (i < rt->scene.num_spheres)
		check_sphere_hit(ray, rt->scene.spheres[i++], &hit);
	i = 0;
	while (i < rt->scene.num_planes)
		check_plane_hit(ray, rt->scene.planes[i++], &hit);
	i = 0;
	while (i < rt->scene.num_cylinders)
		check_cylinder_hit(ray, rt->scene.cylinders[i++], &hit);
	if (hit.hit_anything)
	{
		lit_color = calculate_lighting(rt, &hit);
		return (rgb_to_int(lit_color));
	}
	return (0);
}
