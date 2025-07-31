/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:53:52 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 18:26:52 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Normal = normalized(point - center) */
t_v3d	sphere_normal(t_v3d point, t_sphere sphere)
{
	return (normalize_vector(vec_sub(point, sphere.center)));
}

t_v3d	plane_normal(t_plane plane)
{
	return (plane.normal);
}

t_color	apply_ambient(t_color object_color, t_ambient ambient)
{
	t_color	result;

	result.r = object_color.r * ambient.ratio;
	result.g = object_color.g * ambient.ratio;
	result.b = object_color.b * ambient.ratio;
	return (result);
}

t_color	calculate_diffuse(t_color object_color, t_v3d normal,
			t_v3d light_dir, double intensity)
{
	double	dot;
	t_color	result;

	dot = vec_dot(normal, light_dir);
	if (dot < 0)
		dot = 0;
	dot *= intensity;
	result.r = fmin(255, object_color.r * dot);
	result.g = fmin(255, object_color.g * dot);
	result.b = fmin(255, object_color.b * dot);
	return (result);
}

t_color	add_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = fmin(255, c1.r + c2.r);
	result.g = fmin(255, c1.g + c2.g);
	result.b = fmin(255, c1.b + c2.b);
	return (result);
}
