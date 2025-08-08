/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:13:45 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/06 15:36:47 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Calculate hit point from ray and distance */
t_v3d	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, sc_mult(ray.direction, t)));
}

t_v3d	get_sphere_normal(t_v3d hit_point, t_sphere sphere)
{
	t_v3d	normal;

	normal = vec_sub(hit_point, sphere.center);
	return (normalize_vector(normal));
}

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

void	check_cylinder_hit(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
	double	t;

	t = intersect_cylinder(ray, cylinder);
	if (t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->point = ray_at(ray, t);
		hit->normal = get_cylinder_normal(hit->point, cylinder);
		hit->color = cylinder.color;
		hit->hit_anything = 1;
	}
}
