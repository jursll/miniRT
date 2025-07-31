/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_builder2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:15:51 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:19:27 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	init_elements(t_scene *dst, const t_parsed_scene *p)
{
	dst->ambient.ratio = p->ambient.ratio;
	dst->ambient.color = p->ambient.color;
	dst->camera.position = p->cam.coord;
	dst->camera.orientation = p->cam.ori;
	dst->camera.fov = p->cam.fov;
}

static int	count_planes(const t_parsed_scene *p)
{
	int				count;
	t_parsed_object	*o;

	count = 0;
	o = p->obj;
	while (o)
	{
		if (o->type == PLANE)
			count++;
		o = o->next;
	}
	return (count);
}

static void	fill_planes(t_scene *dst, const t_parsed_scene *p)
{
	int				i;
	t_parsed_object	*o;

	i = 0;
	o = p->obj;
	while (o)
	{
		if (o->type == PLANE)
		{
			dst->planes[i].point = o->fig.pl.coord;
			dst->planes[i].normal = o->fig.pl.ori;
			dst->planes[i].color = o->fig.pl.color;
			i++;
		}
		o = o->next;
	}
}

void	init_planes(t_scene *dst, const t_parsed_scene *p)
{
	int	count;

	count = count_planes(p);
	dst->num_planes = count;
	dst->planes = malloc(sizeof * dst->planes * count);
	if (count && !dst->planes)
		print_error("Could not allocate planes");
	fill_planes(dst, p);
}
