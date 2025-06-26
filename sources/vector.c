/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:03:48 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/26 16:57:36 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_v3d	vec(double x, double y, double z)
{
	t_v3d v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_v3d	vec_add(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_v3d	vec_sub(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_v3d	vec_mult(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}

t_v3d	vec_cross(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}
