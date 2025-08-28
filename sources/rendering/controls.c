/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:35:22 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:55:30 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	select_next_object(t_rt *rt)
{
	int	total_objects;

	total_objects = get_total_objects(rt);
	rt->selection_index = (rt->selection_index + 1) % total_objects;
	rt->current_selection = get_selection_at_index(rt, rt->selection_index);
}

void	select_previous_object(t_rt *rt)
{
	int	total_objects;

	total_objects = get_total_objects(rt);
	rt->selection_index = (rt->selection_index - 1 + total_objects)
		% total_objects;
	rt->current_selection = get_selection_at_index(rt, rt->selection_index);
}

void	rotate_camera(t_camera *cam, double yaw, double pitch)
{
	t_v3d	new_orientation;

	cam->orientation = rotate_y(cam->orientation, yaw);
	new_orientation = rotate_x(cam->orientation, pitch);
	if (new_orientation.y < 0.99 && new_orientation.y > -0.99)
		cam->orientation = new_orientation;
	cam->orientation = normalize_vector(cam->orientation);
}

void	move_camera_special(t_camera *cam, t_v3d movement)
{
	t_v3d	world_up;
	t_v3d	cam_right;
	t_v3d	final_movement;

	if (movement.z != 0)
	{
		final_movement = sc_mult(cam->orientation, movement.z);
		cam->position = vec_add(cam->position, final_movement);
		return ;
	}
	if (movement.x != 0)
	{
		world_up = vec(0, 1, 0);
		cam_right = vec_cross(world_up, cam->orientation);
		cam_right = normalize_vector(cam_right);
		final_movement = sc_mult(cam_right, movement.x);
		cam->position = vec_add(cam->position, final_movement);
	}
	if (movement.y != 0)
	{
		cam->position.y += movement.y;
	}
}
