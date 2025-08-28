/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:13:30 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:56:16 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	move_selected_object(t_rt *rt, t_v3d movement)
{
	t_selection	sel;

	sel = rt->current_selection;
	if (sel.type == SEL_CAMERA)
	{
		move_camera_relative(&rt->scene.camera, movement);
	}
	else if (sel.type == SEL_SPHERE)
		rt->scene.spheres[sel.index].center
			= vec_add(rt->scene.spheres[sel.index].center, movement);
	else if (sel.type == SEL_PLANE)
		rt->scene.planes[sel.index].point
			= vec_add(rt->scene.planes[sel.index].point, movement);
	else if (sel.type == SEL_CYLINDER)
		rt->scene.cylinders[sel.index].center
			= vec_add(rt->scene.cylinders[sel.index].center, movement);
	else if (sel.type == SEL_LIGHT)
		rt->scene.lights[sel.index].position
			= vec_add(rt->scene.lights[sel.index].position, movement);
}

void	rotate_selected_object(t_rt *rt, double yaw, double pitch)
{
	t_selection	sel;

	sel = rt->current_selection;
	if (sel.type == SEL_CAMERA)
	{
		rotate_camera(&rt->scene.camera, yaw, pitch);
	}
	else if (sel.type == SEL_PLANE)
	{
		rt->scene.planes[sel.index].normal
			= rotate_y(rt->scene.planes[sel.index].normal, yaw);
		rt->scene.planes[sel.index].normal
			= rotate_x(rt->scene.planes[sel.index].normal, pitch);
		rt->scene.planes[sel.index].normal
			= normalize_vector(rt->scene.planes[sel.index].normal);
	}
	else if (sel.type == SEL_CYLINDER)
	{
		rt->scene.cylinders[sel.index].axis
			= rotate_y(rt->scene.cylinders[sel.index].axis, yaw);
		rt->scene.cylinders[sel.index].axis
			= rotate_x(rt->scene.cylinders[sel.index].axis, pitch);
		rt->scene.cylinders[sel.index].axis
			= normalize_vector(rt->scene.cylinders[sel.index].axis);
	}
}
