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

static bool	handle_object_parsing(char **tok, t_parsed_scene *scene,
	t_figure type, char **err)
{
	t_parsed_object	o_temp;

	ft_bzero(&o_temp, sizeof o_temp);
	if (type == SPHERE && !safe_parse_sphere(tok, &o_temp, err))
		return (false);
	else if (type == PLANE && !safe_parse_plane(tok, &o_temp, err))
		return (false);
	else if (type == CYLINDER && !safe_parse_cylinder(tok, &o_temp, err))
		return (false);
	add_object(tok, scene, type);
	return (true);
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
		return (handle_object_parsing(tok, scene, SPHERE, err));
	else if (!ft_strcmp(tok[0], "pl"))
		return (handle_object_parsing(tok, scene, PLANE, err));
	else if (!ft_strcmp(tok[0], "cy"))
		return (handle_object_parsing(tok, scene, CYLINDER, err));
	else
	{
		if (err)
			*err = "Unknown element identifier";
		return (false);
	}
}

int	open_and_init(int argc, char **argv, t_parsed_scene *scene)
{
	int	fd;

	if (argc != 2)
		print_error("Usage: ./miniRT <scene.rt>");
	check_rt_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Could not open scene file");
	ft_memset(scene, 0, sizeof(*scene));
	return (fd);
}
