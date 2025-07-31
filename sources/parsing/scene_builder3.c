/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_builder3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:14:55 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:20:15 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	count_cylinders(const t_parsed_scene *p)
{
	int				count;
	t_parsed_object	*o;

	count = 0;
	o = p->obj;
	while (o)
	{
		if (o->type == CYLINDER)
			count++;
		o = o->next;
	}
	return (count);
}

static void	fill_cylinders(t_scene *dst, const t_parsed_scene *p)
{
	int				i;
	t_parsed_object	*o;

	i = 0;
	o = p->obj;
	while (o)
	{
		if (o->type == CYLINDER)
		{
			dst->cylinders[i].center = o->fig.cy.coord;
			dst->cylinders[i].axis = o->fig.cy.vec;
			dst->cylinders[i].diameter = o->fig.cy.r * 2.0;
			dst->cylinders[i].height = o->fig.cy.h;
			dst->cylinders[i].color = o->fig.cy.color;
			i++;
		}
		o = o->next;
	}
}

void	init_cylinders(t_scene *dst, const t_parsed_scene *p)
{
	int	count;

	count = count_cylinders(p);
	dst->num_cylinders = count;
	dst->cylinders = malloc(sizeof * dst->cylinders * count);
	if (count && !dst->cylinders)
		print_error("Could not allocate cylinders");
	fill_cylinders(dst, p);
}
