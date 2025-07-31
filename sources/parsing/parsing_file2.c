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

void	dispatch_tokens(char **tok, t_parsed_scene *scene)
{
	if (!ft_strcmp(tok[0], "A"))
		parse_ambient(tok, scene);
	else if (!ft_strcmp(tok[0], "C"))
		parse_camera(tok, scene);
	else if (!ft_strcmp(tok[0], "L"))
		parse_light(tok, scene);
	else if (!ft_strcmp(tok[0], "sp"))
		add_object(tok, scene, SPHERE);
	else if (!ft_strcmp(tok[0], "pl"))
		add_object(tok, scene, PLANE);
	else if (!ft_strcmp(tok[0], "cy"))
		add_object(tok, scene, CYLINDER);
	else
	{
		free_arr(tok);
		print_error("Unknown element identifier");
	}
}
