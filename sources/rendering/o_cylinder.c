/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:24:23 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/06 15:55:36 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	within_height(t_v3d point, t_cylinder cyl)
{
	t_v3d	pc;
	double	projection;

	pc = vec_sub(point, cyl.center);
	projection = vec_dot(pc, cyl.axis);
	return (projection >= -cyl.height / 2.0 && projection <= cyl.height / 2.0);
}

double	intersect_cap(t_ray ray, t_v3d cap_center, t_v3d normal, double radius)
{
	double	denom;
	double	t;
	t_v3d	p;
	double	dist2;

	denom = vec_dot(ray.direction, normal);
	if (fabs(denom) < 0.0001)
		return (-1);
	t = vec_dot(vec_sub(cap_center, ray.origin), normal) / denom;
	if (t < 0)
		return (-1);
	p = ray_at(ray, t);
	dist2 = vec_dot(vec_sub(p, cap_center), vec_sub(p, cap_center));
	if (dist2 <= radius * radius)
		return (t);
	return (-1);
}

t_v3d	get_cylinder_normal(t_v3d point, t_cylinder cyl)
{
	t_v3d	pc;
	double	projection;
	t_v3d	axis_point;
	t_v3d	normal;

	pc = vec_sub(point, cyl.center);
	projection = vec_dot(pc, cyl.axis);
	if (fabs(projection - cyl.height / 2.0) < 0.0001)
		return (cyl.axis);
	if (fabs(projection + cyl.height / 2.0) < 0.0001)
		return (sc_mult(cyl.axis, -1));
	axis_point = vec_add(cyl.center, sc_mult(cyl.axis, projection));
	normal = vec_sub(point, axis_point);
	return (normalize_vector(normal));
}
