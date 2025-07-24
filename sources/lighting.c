/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:53:52 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 11:12:03 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
** Calculate normal vector at a point on a sphere
** Normal = normalized(point - center)
*/
t_v3d	sphere_normal(t_v3d point, t_sphere sphere)
{
	return (normalize_vector(vec_sub(point, sphere.center)));
}

/*
** Calculate normal for a plane (it's constant everywhere)
*/
t_v3d	plane_normal(t_plane plane)
{
	return (plane.normal);  // Already normalized
}

/*
** Apply ambient lighting
** This ensures objects are never completely black
*/
t_color	apply_ambient(t_color object_color, t_ambient ambient)
{
	t_color	result;

	result.r = object_color.r * ambient.ratio;
	result.g = object_color.g * ambient.ratio;
	result.b = object_color.b * ambient.ratio;
	return (result);
}

/*
** Calculate diffuse lighting (how light hits surfaces)
**
** Diffuse intensity = max(0, normal · light_direction)
** - If normal faces light: bright (dot product near 1)
** - If normal perpendicular to light: dark (dot product near 0)
** - If normal faces away from light: no light (dot product negative)
*/
t_color	calculate_diffuse(t_color object_color, t_v3d normal,
			t_v3d light_dir, double intensity)
{
	double	dot;
	t_color	result;

	// Calculate how much light hits surface
	dot = vec_dot(normal, light_dir);
	if (dot < 0)
		dot = 0;  // No negative light

	// Apply light intensity and brightness
	dot *= intensity;

	// Calculate final color
	result.r = fmin(255, object_color.r * dot);
	result.g = fmin(255, object_color.g * dot);
	result.b = fmin(255, object_color.b * dot);

	return (result);
}

/*
** Combine ambient and diffuse lighting
*/
t_color	add_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = fmin(255, c1.r + c2.r);
	result.g = fmin(255, c1.g + c2.g);
	result.b = fmin(255, c1.b + c2.b);
	return (result);
}
