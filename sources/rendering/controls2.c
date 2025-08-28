/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:22:07 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:58:38 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	handle_selection_key(int keycode, t_rt *rt)
{
	if (keycode == KEY_N)
		select_next_object(rt);
	else if (keycode == KEY_B)
		select_previous_object(rt);
}

void	handle_movement_key(int keycode, t_rt *rt, double move_speed)
{
	t_v3d	movement;

	if (keycode == KEY_S)
		movement = vec(0, 0, move_speed);
	else if (keycode == KEY_W)
		movement = vec(0, 0, -move_speed);
	else if (keycode == KEY_D)
		movement = vec(-move_speed, 0, 0);
	else if (keycode == KEY_A)
		movement = vec(move_speed, 0, 0);
	else if (keycode == KEY_E)
		movement = vec(0, move_speed, 0);
	else if (keycode == KEY_Q)
		movement = vec(0, -move_speed, 0);
	else
		return ;
	if (rt->current_selection.type == SEL_CAMERA)
		move_camera_relative(&rt->scene.camera, movement);
	else
		move_selected_object(rt, movement);
}

void	handle_rotation_key(int keycode, t_rt *rt, double rotate_speed)
{
	if (keycode == KEY_LEFT)
		rotate_selected_object(rt, -rotate_speed, 0);
	else if (keycode == KEY_RIGHT)
		rotate_selected_object(rt, rotate_speed, 0);
	else if (keycode == KEY_UP)
		rotate_selected_object(rt, 0, -rotate_speed);
	else if (keycode == KEY_DOWN)
		rotate_selected_object(rt, 0, rotate_speed);
}

void	handle_zoom_key(int keycode, t_rt *rt)
{
	if (rt->current_selection.type != SEL_CAMERA)
		return ;
	if (keycode == KEY_P && rt->scene.camera.fov > 10)
		rt->scene.camera.fov -= 5;
	else if (keycode == KEY_M && rt->scene.camera.fov < 170)
		rt->scene.camera.fov += 5;
}

int	handle_key(int keycode, t_rt *rt)
{
	const double	move_speed = 1.0;
	const double	rotate_speed = 0.1;

	if (keycode == KEY_ESC)
		destroy(rt);
	else if (keycode == KEY_N || keycode == KEY_B)
		handle_selection_key(keycode, rt);
	else if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_Q || keycode == KEY_E)
		handle_movement_key(keycode, rt, move_speed);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		handle_rotation_key(keycode, rt, rotate_speed);
	else if (keycode == KEY_P || keycode == KEY_M)
		handle_zoom_key(keycode, rt);
	else
		return (0);
	display(rt);
	return (0);
}
