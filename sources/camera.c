/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:24:16 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/26 16:23:22 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_ray generate_ray(t_camera *cam, int px, int py, int img_w, int img_h)
{
	t_vec	up;
	t_vec	x_cam;
	t_vec	ray_dir;
	double	nx;
	double	ny;
	double	scale;
	double	tan_fov2;
	t_ray	ray;

	/* world up vector */
	up = vec(0, 1, 0);
	/* right axis */
	x_cam = vec_norm(vec_cross(cam->dir, up));
	/* screen projection scale */
	scale = tan((cam->fov * M_PI / 180.0) / 2.0);
	/* normalized device coords */
	nx = (px + 0.5) / img_w;
	 ny = (py + 0.5) / img_h;
	/* screen space coords */
	nx = 2.0 * nx - 1.0;
	 ny = 1.0 - 2.0 * ny;
	/* adjust for aspect ratio and FOV */
	nx *= scale * ((double)img_w / img_h);
	 ny *= scale;
	/* compute ray direction */
	ray_dir = vec_mul(x_cam, nx);
	ray_dir = vec_add(ray_dir,
		 vec_mul(vec_cross(x_cam, cam->dir), ny));
	ray_dir = vec_add(ray_dir, cam->dir);
	/* finalize ray */
	ray.origin = cam->origin;
	ray.dir = vec_norm(ray_dir);
	return (ray);
}
