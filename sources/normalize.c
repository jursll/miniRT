/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:30:14 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/04 16:31:18 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Normalizes a vector (makes its length = 1) */
t_v3d	normalize_vector(t_v3d v)
{
	double	length;
	t_v3d	normalized;

	length = vec_norm(v);
	if (length == 0)
		return (v);
	normalized.x = v.x / length;
	normalized.y = v.y / length;
	normalized.z = v.z / length;
	return (normalized);
}

/* Creates a ray with normalized direction */
t_ray	create_ray(t_v3d origin, t_v3d direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = normalize_vector(direction);
	return (ray);
}
