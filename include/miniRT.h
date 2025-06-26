/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:28:02 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/26 17:23:17 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# define WIN_W 1200
# define WIN_H 800
# define E 1e-4


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

// -------- OBJECTS -------- //

typedef struct s_plane
{
	char	*id;
	t_v3d	coord;
	t_v3d	ori;
	t_color	color;
}	t_plane;

typedef struct s_sphere
{
	char	*id;
	t_v3d	coord;
	double	r;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	char	*id;
	t_v3d	coord;
	t_v3d	norm_vec;
	double	r;
	double	h;
	t_color	color;

}	t_cylinder;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

enum e_figure
{
	SPHERE,
	PLANE,
	CYLINDER
};

/* Linked list for all the objects in the scene */
typedef struct s_objects
{
	int					i;
	enum e_figure		type;
	union u_figures		fig;
	struct s_objects	*next;
}	t_objects;

// -------- SCENE -------- //

typedef struct s_ambiant
{
	char	*id;
	float	ratio;
	t_color	color;
}	t_ambiant;

typedef struct s_camera
{
	char	*id;
	double	fov;
	t_v3d	coord;
	t_v3d	ori;
}	t_camera;

typedef struct s_light
{
	char	*id;
	float	ratio;
	t_v3d	coord;
}	t_light;

/* A scene is defined by some objects,
two lights (ambiant & point of light) & one camera */
typedef struct s_scene
{
	t_ambiant	amb;
	t_camera	cam;
	t_light		light;
	t_objects	*obj;
}	t_scene;

/* struct for the image of mlbx */
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

/* struct for everything mlbx related */
typedef struct s_mlbx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}	t_mlbx;

/* struct for intersections */
typedef struct s_inter
{
	int				i;
	enum e_figure	type;
	union u_figures	obj;
	double			dist;
	t_v3d			point;
	t_v3d			normal;
	t_color			c;
}	t_inter;

/* A single ray */
typedef struct s_ray
{
	t_v3d	v_dir;
	t_v3d	coord;
	t_inter	*inter;
}	t_ray;

// -------- MAIN STRUCT -------- //

typedef struct s_rt
{
	int		win_w;
	int		win_h;
	t_mlbx	*mlbx;
	t_scene	*sc;
}	t_rt;


// -------- mlbx.c -------- //

int		esc_key(const int keycode, t_rt *rt);
void	make_window(t_rt *rt);
int		destroy(t_rt *rt);
int		display(t_rt *rt);
void	my_mlx_pixel_put(t_img img, int x, int y, int color);


// -------- vector.c -------- //

t_v3d	vec(double x, double y, double z);
t_v3d	vec_add(t_v3d a, t_v3d b);
t_v3d	vec_sub(t_v3d a, t_v3d b);
t_v3d	vec_mul(t_v3d a, t_v3d b);
t_v3d	sc_mul(t_v3d a, double nb);
double	vec_dot(t_v3d a, t_v3d b);
t_v3d	vec_cross(t_v3d a, t_v3d b);
double	vec_norm(t_v3d a);


// -------- math.c -------- //

double	quad(double a, double b, double c);
double	dot_product(t_v3d a, t_v3d b);
int		rgb_to_int(t_color rgb);
double	dst(t_v3d *p1, t_v3d *p2);


// -------- camera.c -------- //

t_ray generate_ray(t_camera *cam, int px, int py, int img_w, int img_h);

#endif
