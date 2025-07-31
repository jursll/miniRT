/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:27:18 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 16:52:36 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Initialize selection in your main or scene creation */
void	init_selection(t_rt *rt)
{
	rt->selection_index = 0;  /* Start with camera selected */
	rt->current_selection = get_selection_at_index(rt, 0);
}

/* Get total number of selectable objects */
int	get_total_objects(t_rt *rt)
{
	int	total;

	total = 1;  // Camera is always selectable
	total += rt->scene.num_spheres;
	total += rt->scene.num_planes;
	total += rt->scene.num_cylinders;
	total += rt->scene.num_lights;
	return (total);
}

/* Get selection info for current index */
t_selection	get_selection_at_index(t_rt *rt, int sel_index)
{
	t_selection	sel;
	int			current;

	current = 0;

	/* Camera is always first */
	if (sel_index == current)
	{
		sel.type = SEL_CAMERA;
		sel.index = 0;
		sprintf(sel.name, "Camera");
		return (sel);
	}
	current++;

	/* Spheres */
	if (sel_index < current + rt->scene.num_spheres)
	{
		sel.type = SEL_SPHERE;
		sel.index = sel_index - current;
		sprintf(sel.name, "Sphere %d", sel.index + 1);
		return (sel);
	}
	current += rt->scene.num_spheres;

	/* Planes */
	if (sel_index < current + rt->scene.num_planes)
	{
		sel.type = SEL_PLANE;
		sel.index = sel_index - current;
		sprintf(sel.name, "Plane %d", sel.index + 1);
		return (sel);
	}
	current += rt->scene.num_planes;

	/* Cylinders */
	if (sel_index < current + rt->scene.num_cylinders)
	{
		sel.type = SEL_CYLINDER;
		sel.index = sel_index - current;
		sprintf(sel.name, "Cylinder %d", sel.index + 1);
		return (sel);
	}
	current += rt->scene.num_cylinders;

	/* Lights */
	sel.type = SEL_LIGHT;
	sel.index = sel_index - current;
	sprintf(sel.name, "Light %d", sel.index + 1);
	return (sel);
}

/* Move selected object */
void	move_selected_object(t_rt *rt, t_v3d movement)
{
	t_selection	sel;

	sel = rt->current_selection;

	if (sel.type == SEL_CAMERA)
	{
		/* Camera moves relative to its orientation */
		move_camera_relative(&rt->scene.camera, movement);
	}
	else if (sel.type == SEL_SPHERE)
		rt->scene.spheres[sel.index].center = vec_add(rt->scene.spheres[sel.index].center, movement);
	else if (sel.type == SEL_PLANE)
		rt->scene.planes[sel.index].point = vec_add(rt->scene.planes[sel.index].point, movement);
	else if (sel.type == SEL_CYLINDER)
		rt->scene.cylinders[sel.index].center = vec_add(rt->scene.cylinders[sel.index].center, movement);
	else if (sel.type == SEL_LIGHT)
		rt->scene.lights[sel.index].position = vec_add(rt->scene.lights[sel.index].position, movement);
}

/* Rotate selected object (only for objects with orientation) */
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
		/* Rotate plane normal */
		rt->scene.planes[sel.index].normal = rotate_y(rt->scene.planes[sel.index].normal, yaw);
		rt->scene.planes[sel.index].normal = rotate_x(rt->scene.planes[sel.index].normal, pitch);
		rt->scene.planes[sel.index].normal = normalize_vector(rt->scene.planes[sel.index].normal);
	}
	else if (sel.type == SEL_CYLINDER)
	{
		/* Rotate cylinder axis */
		rt->scene.cylinders[sel.index].axis = rotate_y(rt->scene.cylinders[sel.index].axis, yaw);
		rt->scene.cylinders[sel.index].axis = rotate_x(rt->scene.cylinders[sel.index].axis, pitch);
		rt->scene.cylinders[sel.index].axis = normalize_vector(rt->scene.cylinders[sel.index].axis);
	}
	/* Spheres and lights don't rotate */
}

/* Get object info string for display */
void	get_object_info(t_rt *rt, char *info_str)
{
	t_selection	sel;
	t_v3d		pos;

	sel = rt->current_selection;

	if (sel.type == SEL_CAMERA)
	{
		pos = rt->scene.camera.position;
		sprintf(info_str, "%s | Pos: (%.1f, %.1f, %.1f) | FOV: %d°",
			sel.name, pos.x, pos.y, pos.z, (int)rt->scene.camera.fov);
	}
	else if (sel.type == SEL_SPHERE)
	{
		pos = rt->scene.spheres[sel.index].center;
		sprintf(info_str, "%s | Pos: (%.1f, %.1f, %.1f) | Diameter: %.1f",
			sel.name, pos.x, pos.y, pos.z, rt->scene.spheres[sel.index].diameter);
	}
	else if (sel.type == SEL_PLANE)
	{
		pos = rt->scene.planes[sel.index].point;
		sprintf(info_str, "%s | Pos: (%.1f, %.1f, %.1f) | Normal: (%.2f, %.2f, %.2f)",
			sel.name, pos.x, pos.y, pos.z,
			rt->scene.planes[sel.index].normal.x,
			rt->scene.planes[sel.index].normal.y,
			rt->scene.planes[sel.index].normal.z);
	}
	else if (sel.type == SEL_CYLINDER)
	{
		pos = rt->scene.cylinders[sel.index].center;
		sprintf(info_str, "%s | Pos: (%.1f, %.1f, %.1f) | D: %.1f | H: %.1f",
			sel.name, pos.x, pos.y, pos.z,
			rt->scene.cylinders[sel.index].diameter,
			rt->scene.cylinders[sel.index].height);
	}
	else if (sel.type == SEL_LIGHT)
	{
		pos = rt->scene.lights[sel.index].position;
		sprintf(info_str, "%s | Pos: (%.1f, %.1f, %.1f) | Brightness: %.1f",
			sel.name, pos.x, pos.y, pos.z, rt->scene.lights[sel.index].brightness);
	}
}

/* Draw info text on screen using MLX */
void	draw_selection_info(t_rt *rt)
{
	char	info_str[256];

	get_object_info(rt, info_str);

	/* Draw black background for text visibility */
	for (int y = 10; y < 30; y++)
		for (int x = 10; x < 600; x++)
			my_mlx_pixel_put(rt->mlbx->img, x, y, 0x000000);

	/* Draw text (MLX string_put must be called after image is displayed) */
	mlx_string_put(rt->mlbx->mlx, rt->mlbx->mlx_win, 15, 25, 0xFFFFFF, info_str);
}
