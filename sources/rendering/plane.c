/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:50:33 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 10:52:38 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
** Ray-plane intersection
**
** A plane is defined by:
** - A point on the plane (plane.point)
** - A normal vector perpendicular to the plane (plane.normal)
**
** The equation is: (P - plane_point) · normal = 0
** Where P is any point on the plane
**
** For ray intersection:
** Ray: P = origin + t * direction
**
** Substituting into plane equation and solving for t:
** t = (plane_point - origin) · normal / (direction · normal)
*/
double	intersect_plane(t_ray ray, t_plane plane)
{
	double	denominator;
	double	t;
	t_v3d	p0_to_origin;

	// Check if ray is parallel to plane
	denominator = vec_dot(ray.direction, plane.normal);

	// If denominator is close to 0, ray is parallel to plane
	if (fabs(denominator) < 0.0001)
		return (-1);

	// Calculate distance along ray to intersection
	p0_to_origin = vec_sub(plane.point, ray.origin);
	t = vec_dot(p0_to_origin, plane.normal) / denominator;

	// Return -1 if intersection is behind ray origin
	if (t < 0)
		return (-1);

	return (t);
}
