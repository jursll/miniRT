/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:49:59 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:37:59 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	add_object(char **tok, t_parsed_scene *scene, t_figure type)
{
	t_parsed_object	*o;
	t_parsed_object	*tail;

	o = malloc (sizeof * o);
	if (!o)
		print_error("Could not allocate object");
	ft_bzero (o, sizeof * o);
	o->type = type;
	if (type == SPHERE)
		parse_sphere(tok, o);
	else if (type == PLANE)
		parse_plane(tok, o);
	else
		parse_cylinder(tok, o);
	o->next = NULL;
	if (!scene->obj)
		scene->obj = o;
	else
	{
		tail = scene->obj;
		while (tail->next)
			tail = tail->next;
		tail->next = o;
	}
}

bool	dispatch_tokens(char **tok, t_parsed_scene *scene, char **err)
{
	if (!ft_strcmp(tok[0], "A"))
		return (safe_parse_ambient(tok, scene, err));
	else if (!ft_strcmp(tok[0], "C"))
		return (safe_parse_camera(tok, scene, err));
	else if (!ft_strcmp(tok[0], "L"))
		return (safe_parse_light(tok, scene, err));
	else if (!ft_strcmp(tok[0], "sp"))
	{
		t_parsed_object	o_temp;

		ft_bzero(&o_temp, sizeof o_temp);
		if (!safe_parse_sphere(tok, &o_temp, err))
			return (false);
		add_object(tok, scene, SPHERE);
		return (true);
	}
	else if (!ft_strcmp(tok[0], "pl"))
	{
		t_parsed_object	o_temp;

		ft_bzero(&o_temp, sizeof o_temp);
		if (!safe_parse_plane(tok, &o_temp, err))
			return (false);
		add_object(tok, scene, PLANE);
		return (true);
	}
	else if (!ft_strcmp(tok[0], "cy"))
	{
		t_parsed_object	o_temp;

		ft_bzero(&o_temp, sizeof o_temp);
		if (!safe_parse_cylinder(tok, &o_temp, err))
			return (false);
		add_object(tok, scene, CYLINDER);
		return (true);
	}
	else
	{
		if (err) *err = "Unknown element identifier";
		return (false);
	}
	return (true);
}
