/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:15:32 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 18:24:46 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	try_cylinder_hit(t_ray ray, t_cylinder cyl, double *discriminant)
{
	double		a;
	double		b;
	double		c;

	a = compute_a(ray, cyl);
	b = compute_b(ray, cyl);
	c = compute_c(ray, cyl);
	*discriminant = b * b - 4 * a * c;
	return (quad(a, b, c));
}

double	compute_a(t_ray ray, t_cylinder cyl)
{
	t_v3d	d;
	t_v3d	axis;

	axis = cyl.axis;
	d = vec_sub(ray.direction, sc_mult(axis, vec_dot(ray.direction, axis)));
	return (vec_dot(d, d));
}

double	compute_b(t_ray ray, t_cylinder cyl)
{
	t_v3d	oc;
	t_v3d	axis;
	t_v3d	oc_perp;
	t_v3d	d_perp;

	axis = cyl.axis;
	oc = vec_sub(ray.origin, cyl.center);
	oc_perp = vec_sub(oc, sc_mult(axis, vec_dot(oc, axis)));
	d_perp = vec_sub(ray.direction,
			sc_mult(axis, vec_dot(ray.direction, axis)));
	return (2.0 * vec_dot(oc_perp, d_perp));
}

double	compute_c(t_ray ray, t_cylinder cyl)
{
	t_v3d	oc;
	t_v3d	axis;
	t_v3d	oc_perp;
	double	radius;

	axis = cyl.axis;
	oc = vec_sub(ray.origin, cyl.center);
	oc_perp = vec_sub(oc, sc_mult(axis, vec_dot(oc, axis)));
	radius = cyl.diameter / 2.0;
	return (vec_dot(oc_perp, oc_perp) - radius * radius);
}

double	intersect_infinite_cylinder(t_ray ray, t_cylinder cyl)
{
	double		t1;
	double		t2;
	double		discriminant;

	t1 = try_cylinder_hit(ray, cyl, &discriminant);
	if (t1 >= 0 && within_height(ray_at(ray, t1), cyl))
		return (t1);
	if (discriminant > 0)
	{
		t2 = (-compute_b(ray, cyl) + sqrt(discriminant))
			/ (2 * compute_a(ray, cyl));
		if (t2 > 0 && within_height(ray_at(ray, t2), cyl))
			return (t2);
	}
	return (-1);
}
