/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:33:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 15:23:31 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
	Calculate ray direction for a pixel
	This creates a ray from camera through each pixel
*/
t_v3d	calculate_ray_direction(t_camera cam, int x, int y)
{
	double	fov_rad;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;
	t_v3d	direction;

	// Convert FOV to radians
	fov_rad = cam.fov * M_PI / 180.0;
	aspect_ratio = (double)WIN_W / (double)WIN_H;

	// Convert pixel coordinates to normalized device coordinates (-1 to 1)
	pixel_x = (2.0 * x / WIN_W - 1.0) * aspect_ratio * tan(fov_rad / 2.0);
	pixel_y = (1.0 - 2.0 * y / WIN_H) * tan(fov_rad / 2.0);

	// For now, assume camera looks along positive Z axis
	// You'll need to improve this to handle camera orientation
	direction.x = pixel_x;
	direction.y = pixel_y;
	direction.z = 1.0;

	return (normalize_vector(direction));
}

/*
	Main rendering loop - cast rays for each pixel
*/
void	launch_rays(t_rt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			// Create ray from camera through pixel
			ray.origin = rt->scene.camera.position;
			ray.direction = calculate_ray_direction(rt->scene.camera, x, y);

			// Trace ray and get color
			color = trace_ray_with_lighting(rt, ray);

			// Put pixel on screen
			my_mlx_pixel_put(rt->mlbx->img, x, y, color);
			x++;
		}
		y++;
	}
}
/*
	REPLACED BY TRACE_RAY_WITH_LIGHTING

int	trace_ray(t_rt *rt, t_ray ray)
{
	double	t;
	double	min_t;
	int		hit_color;
	int		i;

	min_t = INFINITY;
	hit_color = 0; // Black background

	// Check intersection with all spheres
	i = 0;
	while (i < rt->scene.num_spheres)
	{
		t = intersect_sphere(ray, rt->scene.spheres[i]);
		if (t > 0 && t < min_t)
		{
			min_t = t;
			hit_color = rgb_to_int(rt->scene.spheres[i].color);
		}
		i++;
	}

	// Check intersection with all planes
	i = 0;
	while (i < rt->scene.num_planes)
	{
		t = intersect_plane(ray, rt->scene.planes[i]);
		if (t > 0 && t < min_t)
		{
			min_t = t;
			hit_color = rgb_to_int(rt->scene.planes[i].color);
		}
		i++;
	}

	return (hit_color);
}
*/
