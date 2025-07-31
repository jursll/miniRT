/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:22:41 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 18:23:27 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	compute_cap1(t_ray ray, t_cylinder cyl)
{
	t_v3d	cap_center;
	double	radius;

	radius = cyl.diameter / 2.0;
	cap_center = vec_add(cyl.center, sc_mult(cyl.axis, cyl.height / 2.0));
	return (intersect_cap(ray, cap_center, cyl.axis, radius));
}

double	compute_cap2(t_ray ray, t_cylinder cyl)
{
	t_v3d	cap_center;
	double	radius;

	radius = cyl.diameter / 2.0;
	cap_center = vec_sub(cyl.center, sc_mult(cyl.axis, cyl.height / 2.0));
	return (intersect_cap(ray, cap_center, sc_mult(cyl.axis, -1), radius));
}

double	find_closest_positive(double a, double b, double c)
{
	double	min;

	min = INFINITY;
	if (a > 0 && a < min)
		min = a;
	if (b > 0 && b < min)
		min = b;
	if (c > 0 && c < min)
		min = c;
	return (min);
}

double	intersect_cylinder(t_ray ray, t_cylinder cyl)
{
	double	t_body;
	double	t_cap1;
	double	t_cap2;
	double	min_t;

	t_body = intersect_infinite_cylinder(ray, cyl);
	t_cap1 = compute_cap1(ray, cyl);
	t_cap2 = compute_cap2(ray, cyl);
	min_t = find_closest_positive(t_body, t_cap1, t_cap2);
	if (min_t < INFINITY)
		return (min_t);
	return (-1);
}
