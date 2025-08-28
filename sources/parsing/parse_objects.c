/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:35:27 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 15:41:46 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	parse_plane(char **tok, t_parsed_object *o)
{
	parse_coordination_or_exit(tok[1], &o->fig.pl.coord);
	parse_vector_or_exit(tok[2], &o->fig.pl.ori);
	parse_color_or_exit(tok[3], &o->fig.pl.color);
}

void	parse_sphere(char **tok, t_parsed_object *o)
{
	float	diam;

	parse_coordination_or_exit(tok[1], &o->fig.sp.coord);
	{
		diam = parse_d_h_or_exit(tok[2]);
		o->fig.sp.r = diam * 0.5f;
	}
	parse_color_or_exit(tok[3], &o->fig.sp.color);
}

void	parse_cylinder(char **tok, t_parsed_object *o)
{
	float	diam;

	parse_coordination_or_exit(tok[1], &o->fig.cy.coord);
	parse_vector_or_exit(tok[2], &o->fig.cy.vec);
	{
		diam = parse_d_h_or_exit(tok[3]);
		o->fig.cy.r = diam * 0.5f;
	}
	o->fig.cy.h = parse_d_h_or_exit(tok[4]);
	parse_color_or_exit(tok[5], &o->fig.cy.color);
}
