/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_format_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:40:10 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/07 09:41:54 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	format_camera_info(t_rt *rt, char *info_str)
{
	t_v3d	pos;
	char	*fov;
	char	*tmp;

	pos = rt->scene.camera.position;
	fov = ft_itoa((int)rt->scene.camera.fov);
	if (!fov)
		return ;
	ft_strcpy(info_str, rt->current_selection.name);
	ft_strlcat(info_str, " | Pos: ", 100);
	tmp = format_vec(pos, 1);
	ft_strlcat(info_str, tmp, 100);
	free(tmp);
	ft_strlcat(info_str, " | FOV: ", 100);
	ft_strlcat(info_str, fov, 100);
	ft_strlcat(info_str, "°", 100);
	free(fov);
}

void	format_sphere_info(t_rt *rt, char *info_str)
{
	t_v3d	pos;
	char	*diameter;
	char	*tmp;

	pos = rt->scene.spheres[rt->current_selection.index].center;
	diameter = ft_dtoa(rt->scene.spheres[rt->current_selection.index].diameter,
			1);
	if (!diameter)
		return ;
	ft_strcpy(info_str, rt->current_selection.name);
	ft_strlcat(info_str, " | Pos: ", 100);
	tmp = format_vec(pos, 1);
	ft_strlcat(info_str, tmp, 100);
	free(tmp);
	ft_strlcat(info_str, " | Diameter: ", 100);
	ft_strlcat(info_str, diameter, 100);
	free(diameter);
}

void	format_plane_info(t_rt *rt, char *info_str)
{
	t_v3d	pos;
	char	*tmp;
	char	*norm;

	pos = rt->scene.planes[rt->current_selection.index].point;
	norm = format_vec(rt->scene.planes[rt->current_selection.index].normal, 2);
	if (!norm)
		return ;
	ft_strcpy(info_str, rt->current_selection.name);
	ft_strlcat(info_str, " | Pos: ", 100);
	tmp = format_vec(pos, 1);
	ft_strlcat(info_str, tmp, 100);
	free(tmp);
	ft_strlcat(info_str, " | Normal: ", 100);
	ft_strlcat(info_str, norm, 100);
	free(norm);
}

void	format_cylinder_info(t_rt *rt, char *info_str)
{
	t_v3d	pos;
	char	*d;
	char	*h;
	char	*tmp;

	pos = rt->scene.cylinders[rt->current_selection.index].center;
	d = ft_dtoa(rt->scene.cylinders[rt->current_selection.index].diameter, 1);
	h = ft_dtoa(rt->scene.cylinders[rt->current_selection.index].height, 1);
	if (!d || !h)
		return ;
	ft_strcpy(info_str, rt->current_selection.name);
	ft_strlcat(info_str, " | Pos: ", 100);
	tmp = format_vec(pos, 1);
	ft_strlcat(info_str, tmp, 100);
	free(tmp);
	ft_strlcat(info_str, " | D: ", 100);
	ft_strlcat(info_str, d, 100);
	ft_strlcat(info_str, " | H: ", 100);
	ft_strlcat(info_str, h, 100);
	free(d);
	free(h);
}

void	format_light_info(t_rt *rt, char *info_str)
{
	t_v3d	pos;
	char	*b;
	char	*tmp;

	pos = rt->scene.lights[rt->current_selection.index].position;
	b = ft_dtoa(rt->scene.lights[rt->current_selection.index].brightness, 1);
	if (!b)
		return ;
	ft_strcpy(info_str, rt->current_selection.name);
	ft_strlcat(info_str, " | Pos: ", 100);
	tmp = format_vec(pos, 1);
	ft_strlcat(info_str, tmp, 100);
	free(tmp);
	ft_strlcat(info_str, " | Brightness: ", 100);
	ft_strlcat(info_str, b, 100);
	free(b);
}
