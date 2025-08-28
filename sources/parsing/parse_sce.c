/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:22:11 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:21:45 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	parse_ambient(char **tokens, t_parsed_scene *scene)
{
	scene->ambient.ratio = parse_ratio(tokens[1]);
	parse_color(tokens[2], &scene->ambient.color);
	scene->has_ambient = 1;
}

void	parse_light(char **tokens, t_parsed_scene *scene)
{
	parse_coordination(tokens[1], &scene->light.coord);
	scene->light.ratio = parse_ratio(tokens[2]);
	parse_color(tokens[3], &scene->light.color);
	scene->has_light = 1;
}

void	parse_camera(char **tok, t_parsed_scene *sc)
{
	parse_coordination(tok[1], &sc->cam.coord);
	parse_vector(tok[2], &sc->cam.ori);
	sc->cam.fov = string_to_float(tok[3]);
	sc->has_camera = 1;
}

bool	check_light_args(char **tokens, t_parsed_scene *scene,
		char **err)
{
	if (scene->has_light)
		return (set_err(err, "Too many lights"));
	if (counter(tokens) != 4)
		return (set_err(err, "Light needs 3 arguments"));
	if (!parse_coordination(tokens[1], &scene->light.coord))
		return (set_err(err, "Invalid coordinates"));
	if (!is_a_valid_float(tokens[2]))
		return (set_err(err, "Ratio must be a float"));
	return (true);
}

bool	check_camera_args(char **tok, t_parsed_scene *sc, char **err)
{
	if (sc->has_camera)
		return (set_err(err, "Only one camera allowed"));
	if (counter(tok) != 4)
		return (set_err(err, "Camera needs 3 arguments"));
	if (!parse_coordination(tok[1], &sc->cam.coord))
		return (set_err(err, "Invalid coordinates"));
	if (!parse_vector(tok[2], &sc->cam.ori))
		return (set_err(err, "Invalid direction vector"));
	if (!is_a_valid_float(tok[3]))
		return (set_err(err, "FOV must be a float"));
	sc->cam.fov = string_to_float(tok[3]);
	if (sc->cam.fov <= 0.0f || sc->cam.fov > 180.0f)
		return (set_err(err, "FOV must be in (0, 180]"));
	return (true);
}
