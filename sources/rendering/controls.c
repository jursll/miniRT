/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:35:22 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 10:50:14 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Cycle through objects */
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
	rt->selection_index = (rt->selection_index - 1 + total_objects) % total_objects;
	rt->current_selection = get_selection_at_index(rt, rt->selection_index);
}

/* Enhanced handle_key function */
int	handle_key(int keycode, t_rt *rt)
{
	const double	move_speed = 1.0;
	const double	rotate_speed = 0.1;
	t_v3d			movement;

	if (keycode == KEY_ESC)
		destroy(rt);

	/* Selection controls */
	else if (keycode == KEY_TAB)
	{
		/* Check if shift is pressed (you might need to handle this differently) */
		select_next_object(rt);
	}

	/* Movement controls - now work on selected object */
	else if (keycode == KEY_W)  /* Forward/+Z */
	{
		movement = vec(0, 0, move_speed);
		move_selected_object(rt, movement);
	}
	else if (keycode == KEY_S)  /* Backward/-Z */
	{
		movement = vec(0, 0, -move_speed);
		move_selected_object(rt, movement);
	}
	else if (keycode == KEY_A)  /* Left/-X */
	{
		movement = vec(-move_speed, 0, 0);
		move_selected_object(rt, movement);
	}
	else if (keycode == KEY_D)  /* Right/+X */
	{
		movement = vec(move_speed, 0, 0);
		move_selected_object(rt, movement);
	}
	else if (keycode == KEY_Q)  /* Up/+Y */
	{
		movement = vec(0, move_speed, 0);
		move_selected_object(rt, movement);
	}
	else if (keycode == KEY_E)  /* Down/-Y */
	{
		movement = vec(0, -move_speed, 0);
		move_selected_object(rt, movement);
	}

	/* Rotation controls - only for objects that can rotate */
	else if (keycode == KEY_LEFT)
		rotate_selected_object(rt, -rotate_speed, 0);
	else if (keycode == KEY_RIGHT)
		rotate_selected_object(rt, rotate_speed, 0);
	else if (keycode == KEY_UP)
		rotate_selected_object(rt, 0, -rotate_speed);
	else if (keycode == KEY_DOWN)
		rotate_selected_object(rt, 0, rotate_speed);

	/* FOV controls - only work when camera is selected */
	else if (keycode == KEY_P && rt->current_selection.type == SEL_CAMERA)
	{
		if (rt->scene.camera.fov > 10)
			rt->scene.camera.fov -= 5;
	}
	else if (keycode == KEY_M && rt->current_selection.type == SEL_CAMERA)
	{
		if (rt->scene.camera.fov < 170)
			rt->scene.camera.fov += 5;
	}
	else
		return (0);

	/* Re-render the scene */
	display(rt);
	return (0);
}

/* Rotate camera view */
void	rotate_camera(t_camera *cam, double yaw, double pitch)
{
	/* Apply yaw (horizontal rotation) */
	cam->orientation = rotate_y(cam->orientation, yaw);

	/* Apply pitch (vertical rotation) with limits */
	t_v3d new_orientation = rotate_x(cam->orientation, pitch);

	/* Prevent camera from flipping upside down */
	if (new_orientation.y < 0.99 && new_orientation.y > -0.99)
		cam->orientation = new_orientation;

	cam->orientation = normalize_vector(cam->orientation);
}

/* Special camera movement for when camera is selected */
void	move_camera_special(t_camera *cam, t_v3d movement)
{
	t_v3d	world_up;
	t_v3d	cam_right;
//	t_v3d	cam_up;
	t_v3d	final_movement;

	/* If moving along view axis (W/S), use orientation */
	if (movement.z != 0)
	{
		final_movement = sc_mult(cam->orientation, movement.z);
		cam->position = vec_add(cam->position, final_movement);
		return;
	}

	/* For left/right movement, calculate camera right vector */
	if (movement.x != 0)
	{
		world_up = vec(0, 1, 0);
		cam_right = vec_cross(world_up, cam->orientation);
		cam_right = normalize_vector(cam_right);
		final_movement = sc_mult(cam_right, movement.x);
		cam->position = vec_add(cam->position, final_movement);
	}

	/* For up/down, just use Y axis */
	if (movement.y != 0)
	{
		cam->position.y += movement.y;
	}
}
