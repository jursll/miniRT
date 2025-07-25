/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:24:23 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/25 11:08:54 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Check if point is within cylinder height */
int	within_height(t_v3d point, t_cylinder cyl)
{
	t_v3d	pc;
	double	projection;

	/* Project point onto cylinder axis */
	pc = vec_sub(point, cyl.center);
	projection = vec_dot(pc, cyl.axis);

	/* Check if within height bounds */
	return (projection >= -cyl.height / 2.0 && projection <= cyl.height / 2.0);
}

/* Intersection with infinite cylinder (no caps) */
double	intersect_infinite_cylinder(t_ray ray, t_cylinder cyl)
{
	t_v3d	oc;
	t_v3d	d_perp;
	t_v3d	oc_perp;
	double	a, b, c;
	double	radius;
	double	t1, t2;

	radius = cyl.diameter / 2.0;
	oc = vec_sub(ray.origin, cyl.center);

	/* Project ray direction perpendicular to cylinder axis */
	d_perp = vec_sub(ray.direction,
				sc_mult(cyl.axis, vec_dot(ray.direction, cyl.axis)));

	/* Project oc perpendicular to cylinder axis */
	oc_perp = vec_sub(oc, sc_mult(cyl.axis, vec_dot(oc, cyl.axis)));

	/* Quadratic coefficients */
	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(oc_perp, d_perp);
	c = vec_dot(oc_perp, oc_perp) - radius * radius;

	/* Solve quadratic */
	t1 = quad(a, b, c);
	if (t1 < 0)
		return (-1);

	/* Check if first intersection is within cylinder height */
	if (within_height(ray_at(ray, t1), cyl))
		return (t1);

	/* Check second intersection */
	double discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (t2 > 0 && within_height(ray_at(ray, t2), cyl))
			return (t2);
	}

	return (-1);
}

/* Intersection with cylinder cap (circular disc) */
double	intersect_cap(t_ray ray, t_v3d cap_center, t_v3d normal, double radius)
{
	double	denom;
	double	t;
	t_v3d	p;
	double	dist2;

	/* Check if ray is parallel to cap */
	denom = vec_dot(ray.direction, normal);
	if (fabs(denom) < 0.0001)
		return (-1);

	/* Calculate intersection with cap plane */
	t = vec_dot(vec_sub(cap_center, ray.origin), normal) / denom;
	if (t < 0)
		return (-1);

	/* Check if intersection point is within cap radius */
	p = ray_at(ray, t);
	dist2 = vec_dot(vec_sub(p, cap_center), vec_sub(p, cap_center));

	if (dist2 <= radius * radius)
		return (t);

	return (-1);
}

/* Main cylinder intersection function */
double	intersect_cylinder(t_ray ray, t_cylinder cyl)
{
	double	t_body;
	double	t_cap1, t_cap2;
	double	min_t;
	t_v3d	cap1_center, cap2_center;
	double	radius;

	radius = cyl.diameter / 2.0;
	min_t = INFINITY;

	/* Check intersection with cylinder body */
	t_body = intersect_infinite_cylinder(ray, cyl);
	if (t_body > 0 && t_body < min_t)
		min_t = t_body;

	/* Calculate cap centers */
	cap1_center = vec_add(cyl.center, sc_mult(cyl.axis, cyl.height / 2.0));
	cap2_center = vec_sub(cyl.center, sc_mult(cyl.axis, cyl.height / 2.0));

	/* Check top cap */
	t_cap1 = intersect_cap(ray, cap1_center, cyl.axis, radius);
	if (t_cap1 > 0 && t_cap1 < min_t)
		min_t = t_cap1;

	/* Check bottom cap */
	t_cap2 = intersect_cap(ray, cap2_center, sc_mult(cyl.axis, -1), radius);
	if (t_cap2 > 0 && t_cap2 < min_t)
		min_t = t_cap2;

	return (min_t < INFINITY ? min_t : -1);
}

/* Get cylinder normal at hit point */
t_v3d	get_cylinder_normal(t_v3d point, t_cylinder cyl)
{
	t_v3d	pc;
	double	projection;
	t_v3d	axis_point;
	t_v3d	normal;

	pc = vec_sub(point, cyl.center);
	projection = vec_dot(pc, cyl.axis);

	/* Check if on cap */
	if (fabs(projection - cyl.height / 2.0) < 0.0001)
		return (cyl.axis);  /* Top cap */
	if (fabs(projection + cyl.height / 2.0) < 0.0001)
		return (sc_mult(cyl.axis, -1));  /* Bottom cap */

	/* On cylinder body - normal points radially outward */
	axis_point = vec_add(cyl.center, sc_mult(cyl.axis, projection));
	normal = vec_sub(point, axis_point);

	return (normalize_vector(normal));
}
