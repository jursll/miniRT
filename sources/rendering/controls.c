/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:35:22 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/25 15:31:28 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Rotate vector around Y axis (horizontal rotation) */
t_v3d	rotate_y(t_v3d v, double angle)
{
	t_v3d	result;
	double	cos_a = cos(angle);
	double	sin_a = sin(angle);

	result.x = v.x * cos_a + v.z * sin_a;
	result.y = v.y;
	result.z = -v.x * sin_a + v.z * cos_a;
	return (result);
}

/* Rotate vector around X axis (vertical rotation) */
t_v3d	rotate_x(t_v3d v, double angle)
{
	t_v3d	result;
	double	cos_a = cos(angle);
	double	sin_a = sin(angle);

	result.x = v.x;
	result.y = v.y * cos_a - v.z * sin_a;
	result.z = v.y * sin_a + v.z * cos_a;
	return (result);
}

/* Move camera forward/backward along view direction */
void	move_camera_forward(t_camera *cam, double distance)
{
	t_v3d	movement;

	movement = sc_mult(cam->orientation, distance);
	cam->position = vec_add(cam->position, movement);
}

/* Move camera left/right */
void	move_camera_sideway(t_camera *cam, double distance)
{
	t_v3d	right;
	t_v3d	world_up;
	t_v3d	movement;

	world_up = vec(0, 1, 0);

	/* Calculate right vector (cross product of forward and up) */
	right = vec_cross(cam->orientation, world_up);
	right = normalize_vector(right);

	movement = sc_mult(right, distance);
	cam->position = vec_add(cam->position, movement);
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

/* Handle keyboard input */
int	handle_key(int keycode, t_rt *rt)
{
	const double move_speed = 1.0;
	const double rotate_speed = 0.1;

	if (keycode == KEY_ESC)
		destroy(rt);
	/* Movement */
	else if (keycode == KEY_W)  /* Forward */
		move_camera_forward(&rt->scene.camera, move_speed);
	else if (keycode == KEY_S)  /* Backward */
		move_camera_forward(&rt->scene.camera, -move_speed);
	else if (keycode == KEY_A)  /* Left */
		move_camera_sideway(&rt->scene.camera, -move_speed);
	else if (keycode == KEY_D)  /* Right */
		move_camera_sideway(&rt->scene.camera, move_speed);
	else if (keycode == KEY_Q)  /* Up */
		rt->scene.camera.position.y += move_speed;
	else if (keycode == KEY_E)  /* Down */
		rt->scene.camera.position.y -= move_speed;
	/* Rotation */
	else if (keycode == KEY_LEFT)
		rotate_camera(&rt->scene.camera, rotate_speed, 0);
	else if (keycode == KEY_RIGHT)
		rotate_camera(&rt->scene.camera, -rotate_speed, 0);
	else if (keycode == KEY_UP)
		rotate_camera(&rt->scene.camera, 0, -rotate_speed);
	else if (keycode == KEY_DOWN)
		rotate_camera(&rt->scene.camera, 0, rotate_speed);
	/* Zoom (FOV change) */
	else if (keycode == KEY_P && rt->scene.camera.fov > 10)
		rt->scene.camera.fov -= 5;
	else if (keycode == KEY_M && rt->scene.camera.fov < 170)
		rt->scene.camera.fov += 5;
	else
		return (0);

	/* Re-render the scene */
	display(rt);
	return (0);
}
/*
// Mouse drag for smoother rotation (optional)
typedef struct s_mouse
{
	int		pressed;
	int		last_x;
	int		last_y;
}	t_mouse;

int	mouse_press(int button, int x, int y, t_rt *rt)
{
	static t_mouse mouse;

	if (button == 1)  // Left click
	{
		mouse.pressed = 1;
		mouse.last_x = x;
		mouse.last_y = y;
		rt->mlbx->mlx_win = (void *)&mouse;  // Store mouse state
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_rt *rt)
{
	static t_mouse *mouse;

	(void)x;
	(void)y;
	mouse = (t_mouse *)rt->mlbx->mlx_win;
	if (button == 1 && mouse)
		mouse->pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, t_rt *rt)
{
	static t_mouse *mouse;
	double	dx, dy;

	mouse = (t_mouse *)rt->mlbx->mlx_win;
	if (!mouse || !mouse->pressed)
		return (0);

	// Calculate mouse movement
	dx = (x - mouse->last_x) * 0.005;
	dy = (y - mouse->last_y) * 0.005;

	// Rotate camera based on mouse movement
	rotate_camera(&rt->scene.camera, -dx, -dy);

	mouse->last_x = x;
	mouse->last_y = y;

	display(rt);
	return (0);
}
*/
