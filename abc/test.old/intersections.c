/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:22:42 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/04 15:34:20 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_inter	*closest_inter(t_rt *rt, t_ray *ray)
{
	t_inter		*closest;
	t_inter		*temp;
	t_objects	*curr_fig;

	closest = calloc_utils();
	closest->dist = INFINITY;
	curr_fig = rt->sc->obj;
	while (curr_fig)
	{
		closest->i = curr_fig->i;
		if (curr_fig->type == PLANE)
			temp = intersect_plane(ray, &curr_fig->fig.pl);
		else if (curr_fig->type == SPHERE)
			temp = intersect_sphere(ray, &curr_fig->fig.sp);
		else if (curr_fig->type == CYLINDER)
			temp = intersect_cylinder(ray, &curr_fig->fig.cy);
		if (closest && temp->dist > 0 && is_closest(closest, temp))
			free_inter(closest);
		if (closest && temp->dist > 0 && is_closest(closest, temp))
			closest = temp;
		else
			free_inter(temp);
		curr_fig = curr_fig->next;
	}
	return (closest);
}

int	is_closest(t_inter *closest, t_inter *temp)
{
	if (temp->dist == INFINITY && closest->dist)
		return (0);
	if (temp->dist < closest->dist)
		return (1);
	return (0);
}

t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_inter	*inter;
	double	t;
	double	denom;

	inter = calloc_utils();
	plane->ori = normalize(plane->ori);
	denom = dot_product(plane->ori, ray->v_dir);
	if (fabs(denom) < 1e-6)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	t = dot_product(sub(plane->coord, ray->coord), plane->ori) / denom;
	if (t < E)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = PLANE;
	inter->obj.pl = *plane;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	inter->point = add(inter->point, sc_mult(inter->normal, E));
	inter->normal = plane->ori;
	return (inter);
}

t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_inter	*inter;
	t_v3d	oc;
	double	t;

	inter = calloc_utils();
	oc = sub(ray->coord, sphere->coord);
	t = quad(dot_product(ray->v_dir, ray->v_dir),
			2.0 * dot_product(oc, ray->v_dir),
			dot_product(oc, oc) - sphere->r * sphere->r);
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = SPHERE;
	inter->obj.sp = *sphere;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	inter->normal = normalize(sub(inter->point, sphere->coord));
	return (inter);
}
