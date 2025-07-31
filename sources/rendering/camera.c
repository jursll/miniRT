/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:33:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 17:07:34 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Compute camera vectors once per frame */
t_camera_cache	precompute_camera(t_camera cam)
{
	t_camera_cache	cache;
	t_v3d			world_up;
	double			fov_rad;

	world_up = vec(0, 1, 0);
	fov_rad = cam.fov * M_PI / 180.0;
	cache.aspect_ratio = (double)WIN_W / (double)WIN_H;
	cache.fov_scale = tan(fov_rad / 2.0);
	cache.right = vec_cross(world_up, cam.orientation);
	cache.right = normalize_vector(cache.right);
	cache.up = vec_cross(cam.orientation, cache.right);
	cache.up = normalize_vector(cache.up);
	return (cache);
}

t_v3d	calculate_ray_direction(t_camera cam, t_camera_cache *cache,
			int x, int y)
{
	double	pixel_x;
	double	pixel_y;
	t_v3d	direction;

	pixel_x = (2.0 * x / WIN_W - 1.0) * cache->aspect_ratio * cache->fov_scale;
	pixel_y = (1.0 - 2.0 * y / WIN_H) * cache->fov_scale;
	direction = cam.orientation;
	direction = vec_add(direction, sc_mult(cache->right, pixel_x));
	direction = vec_add(direction, sc_mult(cache->up, pixel_y));
	return (normalize_vector(direction));
}

/* Main rendering loop - cast rays for each pixel */
void	launch_rays(t_rt *rt)
{
	int				x;
	int				y;
	t_ray			ray;
	int				color;
	t_camera_cache	cam_cache;

	cam_cache = precompute_camera(rt->scene.camera);
	ray.origin = rt->scene.camera.position;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray.direction = calculate_ray_direction(
					rt->scene.camera, &cam_cache, x, y);
			color = trace_ray(rt, ray);
			my_mlx_pixel_put(rt->mlbx->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	move_camera_relative(t_camera *cam, t_v3d movement)
{
	t_v3d	world_up;
	t_v3d	cam_right;
	t_v3d	cam_forward;
	t_v3d	final_movement;

	world_up = vec(0, 1, 0);
	cam_forward = cam->orientation;
	cam_right = vec_cross(world_up, cam_forward);
	cam_right = normalize_vector(cam_right);
	final_movement = vec(0, 0, 0);
	if (movement.x != 0)
		final_movement = vec_add(final_movement,
				sc_mult(cam_right, movement.x));
	if (movement.y != 0)
		final_movement = vec_add(final_movement, sc_mult(world_up, movement.y));
	if (movement.z != 0)
		final_movement = vec_add(final_movement,
				sc_mult(cam_forward, movement.z));
	cam->position = vec_add(cam->position, final_movement);
}
