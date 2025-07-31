/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:50:33 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 18:36:54 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

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
