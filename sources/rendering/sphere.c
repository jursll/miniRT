/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:32:29 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/04 16:32:38 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_v3d	oc;
	double	a;
	double	b;
	double	c;
	double	radius;

	// Calculate origin to center vector
	oc = vec_sub(ray.origin, sphere.center);

	// Calculate quadratic coefficients
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(oc, ray.direction);

	// Convert diameter to radius
	radius = sphere.diameter / 2.0;
	c = vec_dot(oc, oc) - radius * radius;

	// Use your quad function to solve
	return (quad(a, b, c));
}
