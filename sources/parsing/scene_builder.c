/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:34:37 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 11:35:08 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/parsing.h"

t_scene build_runtime_scene(const t_parsed_scene *p)
{
    t_scene          dst = {0};
    int              count;
    t_parsed_object *o;

    /* 1) Ambient */
    dst.ambient.ratio = p->ambient.ratio;
    dst.ambient.color = p->ambient.color;            // direct

    /* 2) Camera */
    dst.camera.position    = p->cam.coord;           // direct
    dst.camera.orientation = p->cam.ori;             // direct
    dst.camera.fov         = p->cam.fov;

    /* 3) Lights */
    dst.num_lights = p->has_light ? 1 : 0;
    if (dst.num_lights)
    {
        dst.lights = malloc(sizeof *dst.lights * dst.num_lights);
        if (!dst.lights) print_error("Could not allocate lights");
        dst.lights[0].position   = p->light.coord;   // direct
        dst.lights[0].brightness = p->light.ratio;
        dst.lights[0].color      = p->light.color;   // direct
    }

    /* 4) Spheres */
    count = 0;
    for (o = p->obj; o; o = o->next) if (o->type == SPHERE) count++;
    dst.num_spheres = count;
    dst.spheres     = malloc(sizeof *dst.spheres * count);
    if (count && !dst.spheres) print_error("Could not allocate spheres");
    count = 0;
    for (o = p->obj; o; o = o->next)
        if (o->type == SPHERE)
        {
            dst.spheres[count].center   = o->fig.sp.coord;  // direct
            dst.spheres[count].diameter = o->fig.sp.r * 2.0;
            dst.spheres[count].color    = o->fig.sp.color;  // direct
            count++;
        }

    /* 5) Planes */
    count = 0;
    for (o = p->obj; o; o = o->next) if (o->type == PLANE) count++;
    dst.num_planes = count;
    dst.planes     = malloc(sizeof *dst.planes * count);
    if (count && !dst.planes) print_error("Could not allocate planes");
    count = 0;
    for (o = p->obj; o; o = o->next)
        if (o->type == PLANE)
        {
            dst.planes[count].point  = o->fig.pl.coord;   // direct
            dst.planes[count].normal = o->fig.pl.ori;     // direct
            dst.planes[count].color  = o->fig.pl.color;   // direct
            count++;
        }

    /* 6) Cylinders */
    count = 0;
    for (o = p->obj; o; o = o->next) if (o->type == CYLINDER) count++;
    dst.num_cylinders = count;
    dst.cylinders     = malloc(sizeof *dst.cylinders * count);
    if (count && !dst.cylinders) print_error("Could not allocate cylinders");
    count = 0;
    for (o = p->obj; o; o = o->next)
        if (o->type == CYLINDER)
        {
            dst.cylinders[count].center   = o->fig.cy.coord;  // direct
            dst.cylinders[count].axis     = o->fig.cy.vec;    // direct
            dst.cylinders[count].diameter = o->fig.cy.r * 2.0;
            dst.cylinders[count].height   = o->fig.cy.h;
            dst.cylinders[count].color    = o->fig.cy.color;  // direct
            count++;
        }

    return dst;
}
