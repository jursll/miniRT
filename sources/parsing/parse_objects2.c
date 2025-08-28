/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <jjakupi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jjakupi           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	set_error(char **err, char *msg)
{
	if (err)
		*err = msg;
}

bool	safe_parse_plane(char **tok, t_parsed_object *o, char **err)
{
	if (counter(tok) != 4)
		return (set_error(err, "Plane: need 3 args"), false);
	if (!parse_coordination(tok[1], &o->fig.pl.coord))
		return (set_error(err, "Bad coordinates"), false);
	if (!parse_vector(tok[2], &o->fig.pl.ori))
		return (set_error(err, "Bad vector"), false);
	if (!parse_color(tok[3], &o->fig.pl.color))
		return (set_error(err, "Bad color"), false);
	return (true);
}

bool	safe_parse_sphere(char **tok, t_parsed_object *o, char **err)
{
	float	diam;

	if (counter(tok) != 4)
		return (set_error(err, "Sphere: need 3 args"), false);
	if (!parse_coordination(tok[1], &o->fig.sp.coord))
		return (set_error(err, "Bad coordinates"), false);
	if (!parse_d_h(tok[2], &diam))
		return (set_error(err, "Bad diameter"), false);
	o->fig.sp.r = diam * 0.5f;
	if (!parse_color(tok[3], &o->fig.sp.color))
		return (set_error(err, "Bad color"), false);
	return (true);
}

bool	safe_parse_cylinder(char **tok, t_parsed_object *o, char **err)
{
	float	diam;
	float	h;

	if (counter(tok) != 6)
		return (set_error(err, "Cylinder: need 5 args"), false);
	if (!parse_coordination(tok[1], &o->fig.cy.coord))
		return (set_error(err, "Bad coordinates"), false);
	if (!parse_vector(tok[2], &o->fig.cy.vec))
		return (set_error(err, "Bad vector"), false);
	if (!parse_d_h(tok[3], &diam))
		return (set_error(err, "Bad diameter"), false);
	o->fig.cy.r = diam * 0.5f;
	if (!parse_d_h(tok[4], &h))
		return (set_error(err, "Bad height"), false);
	o->fig.cy.h = h;
	if (!parse_color(tok[5], &o->fig.cy.color))
		return (set_error(err, "Bad color"), false);
	return (true);
}
