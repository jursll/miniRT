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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"

bool	safe_parse_ambient(char **tokens, t_parsed_scene *scene, char **err)
{
	if (scene->has_ambient)
		return (err && (*err = "Too many ambient lights"), false);
	if (counter(tokens) != 3)
		return (err && (*err = "Ambient light needs 2 arguments"), false);
	if (!is_a_valid_float(tokens[1]))
		return (err && (*err = "Ratio must be a float"), false);
	scene->ambient.ratio = string_to_float(tokens[1]);
	if (!parse_color(tokens[2], &scene->ambient.color))
		return (err && (*err = "Invalid color format"), false);
	scene->has_ambient = 1;
	return (true);
}

bool	safe_parse_light(char **tokens, t_parsed_scene *scene, char **err)
{
	if (scene->has_light)
		return (err && (*err = "Too many lights"), false);
	if (counter(tokens) != 4)
		return (err && (*err = "Light needs 3 arguments"), false);
	if (!parse_coordination(tokens[1], &scene->light.coord))
		return (err && (*err = "Invalid coordinates"), false);
	if (!is_a_valid_float(tokens[2]))
		return (err && (*err = "Ratio must be a float"), false);
	scene->light.ratio = string_to_float(tokens[2]);
	if (!parse_color(tokens[3], &scene->light.color))
		return (err && (*err = "Invalid color format"), false);
	scene->has_light = 1;
	return (true);
}

bool	safe_parse_camera(char **tok, t_parsed_scene *sc, char **err)
{
	if (sc->has_camera)
		return (err && (*err = "Only one camera allowed"), false);
	if (counter(tok) != 4)
		return (err && (*err = "Camera needs 3 arguments"), false);
	if (!parse_coordination(tok[1], &sc->cam.coord))
		return (err && (*err = "Invalid coordinates"), false);
	if (!parse_vector(tok[2], &sc->cam.ori))
		return (err && (*err = "Invalid direction vector"), false);
	if (!is_a_valid_float(tok[3]))
		return (err && (*err = "FOV must be a float"), false);
	sc->cam.fov = string_to_float(tok[3]);
	if (sc->cam.fov <= 0.0f || sc->cam.fov > 180.0f)
		return (err && (*err = "FOV must be in (0, 180]"), false);
	sc->has_camera = 1;
	return (true);
}

#pragma GCC diagnostic pop
