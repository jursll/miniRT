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
	if (counter(tok) != 4)
		print_error("Plane needs exactly 3 arguments:");
	parse_coordination(tok[1], &o->fig.pl.coord);
	parse_vector(tok[2], &o->fig.pl.ori);
	parse_color(tok[3], &o->fig.pl.color);
}

void	parse_sphere(char **tok, t_parsed_object *o)
{
	float	diam;

	if (counter(tok) != 4)
		print_error("Sphere needs exactly 3 arguments: cent, diam, color");
	parse_coordination(tok[1], &o->fig.sp.coord);
	{
		diam = parse_d_h(tok[2]);
		o->fig.sp.r = diam * 0.5f;
	}
	parse_color(tok[3], &o->fig.sp.color);
}

void	parse_cylinder(char **tok, t_parsed_object *o)
{
	float	diam;

	if (counter(tok) != 6)
		print_error("Cylinder needs exactly 5 arguments");
	parse_coordination(tok[1], &o->fig.cy.coord);
	parse_vector(tok[2], &o->fig.cy.vec);
	{
		diam = parse_d_h(tok[3]);
		o->fig.cy.r = diam * 0.5f;
	}
	o->fig.cy.h = parse_d_h(tok[4]);
	parse_color(tok[5], &o->fig.cy.color);
}

float	parse_d_h(char *s)
{
	char	**parts;
	float	d;

	parts = ft_split(s, ',');
	if (counter(parts) != 1)
		print_error("Only one argument needed");
	free_arr(parts);
	if (!is_a_valid_float(s))
		print_error("Must be a valid number");
	d = string_to_float(s);
	if (d <= 0.0f)
		print_error("Must be greater than 0");
	return (d);
}
