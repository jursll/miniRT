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

bool	safe_parse_plane(char **tok, t_parsed_object *o, char **err)
{
	if (counter(tok) != 4)
	{
		if (err) *err = "Plane needs exactly 3 arguments:";
		return (false);
	}
	if (!safe_parse_coordination(tok[1], &o->fig.pl.coord))
	{
		if (err) *err = "Invalid format. Expected x,y,z";
		return (false);
	}
	if (!safe_parse_vector(tok[2], &o->fig.pl.ori))
	{
		if (err) *err = "Zero vector is not a valid direction";
		return (false);
	}
	if (!safe_parse_color(tok[3], &o->fig.pl.color))
	{
		if (err) *err = "Color components must be digits in [0,255]";
		return (false);
	}
	return (true);
}

bool	safe_parse_sphere(char **tok, t_parsed_object *o, char **err)
{
	float	diam;

	if (counter(tok) != 4)
	{
		if (err) *err = "Sphere needs exactly 3 arguments: cent, diam, color";
		return (false);
	}
	if (!safe_parse_coordination(tok[1], &o->fig.sp.coord))
	{
		if (err) *err = "Invalid format. Expected x,y,z";
		return (false);
	}
	if (!safe_parse_d_h(tok[2], &diam))
	{
		if (err) *err = "Must be greater than 0";
		return (false);
	}
	o->fig.sp.r = diam * 0.5f;
	if (!safe_parse_color(tok[3], &o->fig.sp.color))
	{
		if (err) *err = "Color components must be digits in [0,255]";
		return (false);
	}
	return (true);
}

bool	safe_parse_cylinder(char **tok, t_parsed_object *o, char **err)
{
	float	diam;
	float	h;

	if (counter(tok) != 6)
	{
		if (err) *err = "Cylinder needs exactly 5 arguments";
		return (false);
	}
	if (!safe_parse_coordination(tok[1], &o->fig.cy.coord))
	{
		if (err) *err = "Invalid format. Expected x,y,z";
		return (false);
	}
	if (!safe_parse_vector(tok[2], &o->fig.cy.vec))
	{
		if (err) *err = "Zero vector is not a valid direction";
		return (false);
	}
	if (!safe_parse_d_h(tok[3], &diam))
	{
		if (err) *err = "Must be greater than 0";
		return (false);
	}
	o->fig.cy.r = diam * 0.5f;
	if (!safe_parse_d_h(tok[4], &h))
	{
		if (err) *err = "Must be greater than 0";
		return (false);
	}
	o->fig.cy.h = h;
	if (!safe_parse_color(tok[5], &o->fig.cy.color))
	{
		if (err) *err = "Color components must be digits in [0,255]";
		return (false);
	}
	return (true);
}
