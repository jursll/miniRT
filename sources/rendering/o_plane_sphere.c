/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_plane_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:50:33 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:56:30 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	intersect_plane(t_ray ray, t_plane plane)
{
	double	denominator;
	double	t;
	t_v3d	p0_to_origin;

	denominator = vec_dot(ray.direction, plane.normal);
	if (fabs(denominator) < 0.0001)
		return (-1);
	p0_to_origin = vec_sub(plane.point, ray.origin);
	t = vec_dot(p0_to_origin, plane.normal) / denominator;
	if (t < 0)
		return (-1);
	return (t);
}

double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_v3d	oc;
	double	a;
	double	b;
	double	c;
	double	radius;

	oc = vec_sub(ray.origin, sphere.center);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(oc, ray.direction);
	radius = sphere.diameter / 2.0;
	c = vec_dot(oc, oc) - radius * radius;
	return (quad(a, b, c));
}
