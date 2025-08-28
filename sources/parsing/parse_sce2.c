/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sce2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:22:11 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:21:45 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

bool	set_err(char **err, char *msg)
{
	if (err)
		*err = msg;
	return (false);
}

static bool	check_ambient_args(char **tokens, t_parsed_scene *scene,
		char **err)
{
	if (scene->has_ambient)
		return (set_err(err, "Too many ambient lights"));
	if (counter(tokens) != 3)
		return (set_err(err, "Ambient light needs 2 arguments"));
	if (!is_a_valid_float(tokens[1]))
		return (set_err(err, "Ratio must be a float"));
	return (true);
}

bool	safe_parse_ambient(char **tokens, t_parsed_scene *scene, char **err)
{
	if (!check_ambient_args(tokens, scene, err))
		return (false);
	scene->ambient.ratio = string_to_float(tokens[1]);
	if (!parse_color(tokens[2], &scene->ambient.color))
		return (set_err(err, "Invalid color format"));
	scene->has_ambient = 1;
	return (true);
}

bool	safe_parse_light(char **tokens, t_parsed_scene *scene, char **err)
{
	if (!check_light_args(tokens, scene, err))
		return (false);
	scene->light.ratio = string_to_float(tokens[2]);
	if (!parse_color(tokens[3], &scene->light.color))
		return (set_err(err, "Invalid color format"));
	scene->has_light = 1;
	return (true);
}

bool	safe_parse_camera(char **tok, t_parsed_scene *sc, char **err)
{
	if (!check_camera_args(tok, sc, err))
		return (false);
	sc->has_camera = 1;
	return (true);
}
