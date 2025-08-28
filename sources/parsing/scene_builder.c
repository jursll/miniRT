/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:34:37 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:21:23 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/parsing.h"

static void	init_lights(t_scene *dst, const t_parsed_scene *p)
{
	int	n;

	n = p->has_light;
	dst->num_lights = n;
	if (!n)
		return ;
	dst->lights = malloc(sizeof * dst->lights * n);
	if (!dst->lights)
		print_error("Could not allocate lights");
	dst->lights[0].position = p->light.coord;
	dst->lights[0].brightness = p->light.ratio;
	dst->lights[0].color = p->light.color;
}

static int	count_spheres(const t_parsed_scene *p)
{
	int				count;
	t_parsed_object	*o;

	count = 0;
	o = p->obj;
	while (o)
	{
		if (o->type == SPHERE)
			count++;
		o = o->next;
	}
	return (count);
}

static void	fill_spheres(t_scene *dst, const t_parsed_scene *p)
{
	int				i;
	t_parsed_object	*o;

	i = 0;
	o = p->obj;
	while (o)
	{
		if (o->type == SPHERE)
		{
			dst->spheres[i].center = o->fig.sp.coord;
			dst->spheres[i].diameter = o->fig.sp.r * 2.0;
			dst->spheres[i].color = o->fig.sp.color;
			i++;
		}
		o = o->next;
	}
}

static void	init_spheres(t_scene *dst, const t_parsed_scene *p)
{
	int	count;

	count = count_spheres(p);
	dst->num_spheres = count;
	dst->spheres = malloc(sizeof * dst->spheres * count);
	if (count && !dst->spheres)
		print_error("Could not allocate spheres");
	fill_spheres(dst, p);
}

t_scene	build_runtime_scene(const t_parsed_scene *p)
{
	t_scene	dst;

	dst = (t_scene){0};
	init_elements(&dst, p);
	init_lights(&dst, p);
	init_spheres(&dst, p);
	init_planes(&dst, p);
	init_cylinders(&dst, p);
	return (dst);
}

static void	safe_init_lights(t_scene *dst, const t_parsed_scene *p,
				t_parsed_scene *cleanup)
{
	int	n;

	n = p->has_light;
	dst->num_lights = n;
	if (!n)
		return ;
	dst->lights = malloc(sizeof * dst->lights * n);
	if (!dst->lights)
		cleanup_and_exit(cleanup, -1, "Could not allocate lights");
	dst->lights[0].position = p->light.coord;
	dst->lights[0].brightness = p->light.ratio;
	dst->lights[0].color = p->light.color;
}

static void	safe_init_spheres(t_scene *dst, const t_parsed_scene *p,
				t_parsed_scene *cleanup)
{
	int	count;

	count = count_spheres(p);
	dst->num_spheres = count;
	dst->spheres = malloc(sizeof * dst->spheres * count);
	if (count && !dst->spheres)
		cleanup_and_exit(cleanup, -1, "Could not allocate spheres");
	fill_spheres(dst, p);
}

t_scene	build_runtime_scene_safe(const t_parsed_scene *p,
			t_parsed_scene *to_cleanup)
{
	t_scene	dst;

	dst = (t_scene){0};
	init_elements(&dst, p);
	safe_init_lights(&dst, p, to_cleanup);
	safe_init_spheres(&dst, p, to_cleanup);
	init_planes(&dst, p);
	init_cylinders(&dst, p);
	return (dst);
}
