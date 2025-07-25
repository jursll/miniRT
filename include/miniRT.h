/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:28:02 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/25 14:33:03 by julrusse         ###   ########.fr       */
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

#  define KEY_ESC	65307
#  define KEY_W		119
#  define KEY_S		115
#  define KEY_A		97
#  define KEY_D		100
#  define KEY_Q		113
#  define KEY_E		101
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_UP	65362
#  define KEY_DOWN	65364
#  define KEY_P		112
#  define KEY_M		109

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

/* Structure to store hit information */
typedef struct s_hit
{
	double	t;              // Distance to hit point
	t_v3d	point;          // Where ray hit
	t_v3d	normal;         // Surface normal at hit point
	t_color	color;          // Object color
	int		hit_anything;   // Did we hit something?
}	t_hit;

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
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;       /* Array of lights */
	int			num_lights;
	t_sphere	*spheres;      /* Array of spheres */
	int			num_spheres;
	t_plane		*planes;       /* Array of planes */
	int			num_planes;
	t_cylinder	*cylinders;    /* Array of cylinders */
	int			num_cylinders;
}	t_scene;

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
//	int		trace_ray(t_rt *rt, t_ray ray);  --> replaced by raytacing with lights
void	launch_rays(t_rt *rt);

// -------- raytracing_with_lights.c -------- //
t_v3d	ray_at(t_ray ray, double t);
t_v3d	get_sphere_normal(t_v3d hit_point, t_sphere sphere);
void	check_sphere_hit(t_ray ray, t_sphere sphere, t_hit *hit);
void	check_plane_hit(t_ray ray, t_plane plane, t_hit *hit);
void	check_cylinder_hit(t_ray ray, t_cylinder cylinder, t_hit *hit);
t_color	calculate_lighting(t_rt *rt, t_hit *hit);
int		trace_ray_with_lighting(t_rt *rt, t_ray ray);

// -------- sphere.c -------- //
double	intersect_sphere(t_ray ray, t_sphere sphere);

// -------- plane.c -------- //
double	intersect_plane(t_ray ray, t_plane plane);

// -------- cylinder.c -------- //
int		within_height(t_v3d point, t_cylinder cyl);
double	intersect_infinite_cylinder(t_ray ray, t_cylinder cyl);
double	intersect_cap(t_ray ray, t_v3d cap_center, t_v3d normal, double radius);
double	intersect_cylinder(t_ray ray, t_cylinder cyl);
t_v3d	get_cylinder_normal(t_v3d point, t_cylinder cyl);

// -------- lighting.c -------- //
t_v3d	sphere_normal(t_v3d point, t_sphere sphere);
t_v3d	plane_normal(t_plane plane);
t_color	apply_ambient(t_color object_color, t_ambient ambient);
t_color	calculate_diffuse(t_color object_color, t_v3d normal,
			t_v3d light_dir, double intensity);
t_color	add_colors(t_color c1, t_color c2);

// -------- shadows.c -------- //
int		is_in_shadow(t_rt *rt, t_v3d point, t_v3d light_pos);

// -------- controls.c -------- //
t_v3d	rotate_y(t_v3d v, double angle);
t_v3d	rotate_x(t_v3d v, double angle);
void	move_camera_forward(t_camera *cam, double distance);
void	move_camera_sideway(t_camera *cam, double distance);
void	rotate_camera(t_camera *cam, double yaw, double pitch);
int		handle_key(int keycode, t_rt *rt);

// -------- main.c -------- //
void	create_lit_scene(t_rt *rt);
void	free_rt(t_rt *rt);

#endif
