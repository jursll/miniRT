/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:13:50 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:46:54 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	check_rt_extension(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 3 || ft_strcmp(name + len - 3, ".rt") != 0)
		print_error("Scene file must have a .rt extension");
}

void	validate_scene(t_parsed_scene *scene)
{
	if (!scene->has_ambient)
		print_error("Missing ambient light (A)");
	if (!scene->has_camera)
		print_error("Missing camera (C)");
	if (!scene->has_light)
		print_error("Missing point light (L)");
}

void	validate_scene_with_cleanup(t_parsed_scene *scene)
{
	if (!scene->has_ambient)
		cleanup_and_exit(scene, -1, "Missing ambient light (A)");
	if (!scene->has_camera)
		cleanup_and_exit(scene, -1, "Missing camera (C)");
	if (!scene->has_light)
		cleanup_and_exit(scene, -1, "Missing point light (L)");
}

static bool	handle_line(char *trimmed, t_parsed_scene *scene, int fd)
{
	char	**tokens;
	char	*err;
	bool	success;

	tokens = ft_split(trimmed, ' ');
	free (trimmed);
	if (!tokens)
		cleanup_and_exit(scene, fd, "Malloc failed on split");
	err = NULL;
	success = dispatch_tokens(tokens, scene, &err);
	if (!success)
	{
		free_arr(tokens);
		if (err)
			cleanup_and_exit(scene, fd, err);
		else
			cleanup_and_exit(scene, fd, "Unknown element identifier");
	}
	free_arr(tokens);
	return (true);
}

void	parse_scene_file(int fd, t_parsed_scene *scene)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\r\n");
		free (line);
		normalize_whitespace(trimmed);
		if (*trimmed && *trimmed != '#')
			handle_line(trimmed, scene, fd);
		else
			free(trimmed);
		line = get_next_line(fd);
	}
	close(fd);
}
