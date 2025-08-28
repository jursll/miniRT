/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_system2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:18:06 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:56:40 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_selection	get_selection_at_index(t_rt *rt, int sel_index)
{
	int			current;
	t_selection	sel;

	current = 0;
	if (sel_index == current++)
		return (make_named_selection(0, SEL_CAMERA, "Camera"));
	if (sel_index < current + rt->scene.num_spheres)
		return (make_named_selection(sel_index - current, SEL_SPHERE,
				"Sphere"));
	current += rt->scene.num_spheres;
	if (sel_index < current + rt->scene.num_planes)
		return (make_named_selection(sel_index - current, SEL_PLANE, "Plane"));
	current += rt->scene.num_planes;
	if (sel_index < current + rt->scene.num_cylinders)
		return (make_named_selection(sel_index - current, SEL_CYLINDER,
				"Cylinder"));
	current += rt->scene.num_cylinders;
	if (sel_index < current + rt->scene.num_lights)
		return (make_named_selection(sel_index - current, SEL_LIGHT, "Light"));
	sel.type = SEL_CAMERA;
	sel.index = 0;
	ft_strcpy(sel.name, "Camera");
	return (sel);
}

t_selection	make_camera_selection(void)
{
	t_selection	sel;

	sel.type = SEL_CAMERA;
	sel.index = 0;
	ft_strcpy(sel.name, "Camera");
	return (sel);
}

t_selection	make_named_selection(int index, int type, char *label)
{
	t_selection	sel;
	char		*nb;

	sel.type = type;
	sel.index = index;
	ft_strcpy(sel.name, label);
	nb = ft_itoa(index + 1);
	if (nb)
	{
		ft_strlcat(sel.name, " ", sizeof(sel.name));
		ft_strlcat(sel.name, nb, sizeof(sel.name));
		free(nb);
	}
	return (sel);
}
