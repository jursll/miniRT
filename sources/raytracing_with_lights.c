/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_with_lights.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:13:45 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 15:15:05 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Calculate hit point from ray and distance */
t_v3d	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, sc_mult(ray.direction, t)));
}

/* Get normal for sphere at hit point */
t_v3d	get_sphere_normal(t_v3d hit_point, t_sphere sphere)
{
	t_v3d	normal;

	normal = vec_sub(hit_point, sphere.center);
	return (normalize_vector(normal));
}

/* Check sphere intersection and fill hit info */
void	check_sphere_hit(t_ray ray, t_sphere sphere, t_hit *hit)
{
	double	t;

	t = intersect_sphere(ray, sphere);
	if (t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->point = ray_at(ray, t);
		hit->normal = get_sphere_normal(hit->point, sphere);
		hit->color = sphere.color;
		hit->hit_anything = 1;
	}
}

/* Check plane intersection and fill hit info */
void	check_plane_hit(t_ray ray, t_plane plane, t_hit *hit)
{
	double	t;

	t = intersect_plane(ray, plane);
	if (t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->point = ray_at(ray, t);
		hit->normal = plane.normal;
		hit->color = plane.color;
		hit->hit_anything = 1;
	}
}

/* Calculate lighting at a point */
t_color	calculate_lighting(t_rt *rt, t_hit *hit)
{
	t_color	final_color;
	t_color	ambient;
	t_color	diffuse;
	t_v3d	light_dir;
	double	intensity;
	int		i;

	/* Start with ambient lighting */
	ambient = apply_ambient(hit->color, rt->scene.ambient);
	final_color = ambient;

	/* Add contribution from each light */
	i = 0;
	while (i < rt->scene.num_lights)
	{
		/* Direction from hit point to light */
		light_dir = vec_sub(rt->scene.lights[i].position, hit->point);
		light_dir = normalize_vector(light_dir);

		/* Calculate diffuse lighting (dot product!) */
		intensity = vec_dot(hit->normal, light_dir);
		if (intensity > 0)
		{
			intensity *= rt->scene.lights[i].brightness;
			diffuse = calculate_diffuse(hit->color, hit->normal,
			                           light_dir, intensity);
			final_color = add_colors(final_color, diffuse);
		}
		i++;
	}

	return (final_color);
}

/* Enhanced trace_ray with lighting */
int	trace_ray_with_lighting(t_rt *rt, t_ray ray)
{
	t_hit	hit;
	int		i;

	/* Initialize hit info */
	hit.t = INFINITY;
	hit.hit_anything = 0;

	/* Check all spheres */
	i = 0;
	while (i < rt->scene.num_spheres)
	{
		check_sphere_hit(ray, rt->scene.spheres[i], &hit);
		i++;
	}

	/* Check all planes */
	i = 0;
	while (i < rt->scene.num_planes)
	{
		check_plane_hit(ray, rt->scene.planes[i], &hit);
		i++;
	}

	/* If we hit something, calculate lighting */
	if (hit.hit_anything)
	{
		t_color lit_color = calculate_lighting(rt, &hit);
		return (rgb_to_int(lit_color));
	}

	/* Background color */
	return (0);  // Black
}
