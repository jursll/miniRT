/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:28:02 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/04 17:16:36 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# define WIN_W 800
# define WIN_H 600

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// -------- PLAN & COLORS -------- //

typedef struct s_v3d
{
	double	x;
	double	y;
	double	z;
}	t_v3d;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

// -------- RAY -------- //

typedef struct s_ray
{
	t_v3d	origin;
	t_v3d	direction;
}	t_ray;

// -------- CAMERA -------- //

typedef struct s_camera
{
	t_v3d	position;      /* Camera position in 3D space */
	t_v3d	orientation;   /* Where camera is looking (normalized) */
	double	fov;           /* Field of view in degrees */
}	t_camera;

// -------- AMBIENT LIGHTING -------- //
typedef struct s_ambient
{
	double	ratio;         /* Lighting ratio 0.0-1.0 */
	t_color	color;         /* RGB color */
}	t_ambient;

// -------- LIGHT SOURCE -------- //
typedef struct s_light
{
	t_v3d	position;      /* Light position */
	double	brightness;    /* Brightness ratio 0.0-1.0 */
	t_color	color;         /* RGB color (for bonus) */
}	t_light;

// -------- OBJECTS -------- //
typedef struct s_sphere
{
	t_v3d	center;        /* Sphere center */
	double	diameter;      /* Sphere diameter */
	t_color	color;         /* RGB color */
}	t_sphere;

typedef struct s_plane
{
	t_v3d	point;         /* A point on the plane */
	t_v3d	normal;        /* Normal vector (normalized) */
	t_color	color;         /* RGB color */
}	t_plane;

typedef struct s_cylinder
{
	t_v3d	center;        /* Center of cylinder */
	t_v3d	axis;          /* Axis direction (normalized) */
	double	diameter;      /* Cylinder diameter */
	double	height;        /* Cylinder height */
	t_color	color;         /* RGB color */
}	t_cylinder;

// -------- SCENE -------- //
typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     *lights;       /* Array of lights */
    int         num_lights;
    t_sphere    *spheres;      /* Array of spheres */
    int         num_spheres;
    t_plane     *planes;       /* Array of planes */
    int         num_planes;
    t_cylinder  *cylinders;    /* Array of cylinders */
    int         num_cylinders;
}   t_scene;

// -------- MLX -------- //
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlbx
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
}	t_mlbx;

// -------- MAIN STRUCT -------- //
typedef struct s_rt
{
	t_mlbx	*mlbx;
	t_scene	scene;
}	t_rt;


// -------- mlbx.c -------- //
int		esc_key(const int keycode, t_rt *rt);
void	make_window(t_rt *rt);
int		destroy(t_rt *rt);
int		display(t_rt *rt);
void	my_mlx_pixel_put(t_data img, int x, int y, int color);

// -------- vector.c -------- //
t_v3d	vec(double x, double y, double z);
t_v3d	vec_add(t_v3d a, t_v3d b);
t_v3d	vec_sub(t_v3d a, t_v3d b);
t_v3d	vec_mult(t_v3d a, t_v3d b);
double	vec_dot(t_v3d a, t_v3d b);
t_v3d	vec_cross(t_v3d a, t_v3d b);
double	vec_norm(t_v3d a);

// -------- math.c -------- //
double	quad(double a, double b, double c);
double	dot_product(t_v3d a, t_v3d b);
int		rgb_to_int(t_color rgb);
double	dst(t_v3d *p1, t_v3d *p2);
t_v3d	add(t_v3d a, t_v3d b);
t_v3d	sub(t_v3d a, t_v3d b);
t_v3d	new_v3d(double x, double y, double z);
t_v3d	sc_mult(t_v3d a, double nb);
double	norme(t_v3d a);
t_v3d	cross(t_v3d a, t_v3d b);
t_v3d	mult(t_v3d a, t_v3d b);
double	dot_product_v3d(t_v3d v1, t_v3d v2);

// -------- normalize.c -------- //
t_v3d	normalize_vector(t_v3d v);
t_ray	create_ray(t_v3d origin, t_v3d direction);

// -------- raytracing.c -------- //
t_v3d	calculate_ray_direction(t_camera cam, int x, int y);
int		trace_ray(t_rt *rt, t_ray ray);
void	launch_rays(t_rt *rt);

// -------- raytracing.c -------- //
double	intersect_sphere(t_ray ray, t_sphere sphere);

// -------- main.c -------- //
void	create_test_scene(t_rt *rt);
void	free_rt(t_rt *rt);


/*
// -------- raytracing.c -------- //
double	dist(const t_v3d p1, const t_v3d p2);
t_v3d	normalize(t_v3d a);
void	launch_rays(t_rt *rt);
t_ray	make_ray(t_rt *rt, t_v3d dir);
t_v3d	make_v_dir(t_rt *rt, double x, double y);

// -------- light.c -------- //
int		is_closest(t_inter *closest, t_inter *temp);
void	inter_space(t_ray *ray, t_objects *objects, t_inter **intersection);
void	saving_space(double *max_distance, t_inter	**closest_intersection,
			t_inter	*intersection, bool *is_in_shadow);
t_color	lights_shadows(t_rt *rt, t_scene *sc, t_inter *inter, t_color color);

// -------- colors.c -------- //
t_color	int_to_rgb(const int r, const int g, const int b);
t_color	get_color(t_inter *inter);
t_color	ambiance_color(t_color color, t_ambiant amb);
t_color	shadow_color(t_color color, double shadow_intensity);
t_color	diffuse_color(t_inter *inter, t_light *light, t_color color);

// -------- intersections.c -------- //
t_inter	*closest_inter(t_rt *rt, t_ray *ray);
int		is_closest(t_inter *closest, t_inter *temp);
t_inter	*intersect_plane(t_ray *ray, t_plane *plane);
t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere);
t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder);
int		quad_cylinder(t_ray *ray, t_inter *inter, t_cylinder *cylinder, t_v3d X);
bool	is_intersection_valid(t_ray *ray, t_cylinder *cy, double t, double h);
t_v3d	cylinder_normal(t_v3d P, t_cylinder *cylinder);

// -------- utils.c -------- //
t_inter	*calloc_utils(void);
void	print_v3d(t_v3d vect);
void	print_inter(t_inter *inter);
int		print_error(char *error_message);
void	free_objects(t_rt *rt);
void	free_inter(t_inter *inter);
void	free_tab(char **tab);
void	free_scene(t_scene *scene);
void	free_rt(t_rt *rt);
*/

#endif
