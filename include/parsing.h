/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:26 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:23:51 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "miniRT.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>

/* Ambient light */
typedef struct s__parsed_ambient
{
	float	ratio;
	t_color	color;
}			t_parsed_ambient;

/* Camera */
typedef struct s_parsed_camera
{
	double	fov;
	t_v3d	coord;
	t_v3d	ori;
}			t_parsed_camera;

/* Light */
typedef struct s_parsed_light
{
	float	ratio;
	t_color	color;
	t_v3d	coord;
}			t_parsed_light;

/* Figures */
typedef struct s__parsed_sphere
{
	t_v3d	coord;
	double	r;
	t_color	color;
}			t_parsed_sphere;

typedef struct s_parsed_plane
{
	t_v3d	coord;
	t_v3d	ori;
	t_color	color;
}			t_parsed_plane;

typedef struct s_parsed_cylinder
{
	t_v3d	coord;
	t_v3d	vec;
	double	r;
	double	h;
	t_color	color;
}			t_parsed_cylinder;

/* Figure union and enum */
typedef enum e_figure
{
	SPHERE,
	PLANE,
	CYLINDER
}			t_figure;

typedef union u_figures
{
	t_parsed_sphere		sp;
	t_parsed_plane		pl;
	t_parsed_cylinder	cy;
}			t_figures;

/* Object linked list */
typedef struct s_parsed_object
{
	int						i;
	t_figure				type;
	t_figures				fig;
	struct s_parsed_object	*next;
}			t_parsed_object;

/* Scene */
typedef struct s_parsed_scene
{
	t_parsed_ambient	ambient;
	t_parsed_camera		cam;
	t_parsed_light		light;
	t_parsed_object		*obj;
	int					has_ambient;
	int					has_camera;
	int					has_light;
	int					num_lights;
}				t_parsed_scene;

void		parse_color(char *str, t_color *c);
bool		safe_parse_color(char *str, t_color *c);
bool		safe_parse_coordination(char *str, t_v3d *c);
bool		safe_parse_vector(char *s, t_v3d *v);
bool		safe_parse_d_h(char *s, float *out);
bool		check_color(char *str);
int			is_normalized(t_v3d v);
float		string_to_float(char *str);
int			is_a_valid_float(char *str);
float		abs_val(float x);
int			parse_sign(char *str, int *i);
int			counter(char **tab);
int			print_error(char *error_message);
int			validate_commas(char *s, char sep, int count);
void		parse_ambient(char **tokens, t_parsed_scene *scene);
void		free_arr(char **arr);
void		free_scene_objects(t_parsed_scene *scene);
void		cleanup_and_exit(t_parsed_scene *scene, int fd, char *error_msg);
void		parse_light(char **tokens, t_parsed_scene *scene);
void		parse_coordination(char *str, t_v3d *c);
float		parse_ratio(char *s);
void		parse_camera(char **tok, t_parsed_scene*sc);
void		parse_vector(char *s, t_v3d *v);
void		parse_plane(char **tok, t_parsed_object *o);
float		parse_d_h(char *s);
void		parse_sphere(char **tok, t_parsed_object *o);
void		parse_cylinder(char **tok, t_parsed_object *o);
int			ft_strcmp(const char *s1, const char *s2);
void		validate_scene(t_parsed_scene *scene);
void		validate_scene_with_cleanup(t_parsed_scene *scene);
void		parse_scene_file(int fd, t_parsed_scene *scene);
int			open_and_init(int argc, char **argv, t_parsed_scene *scene);
void		normalize_whitespace(char *s);
void		add_object(char **tok, t_parsed_scene*scene, t_figure type);
bool		safe_parse_ambient(char **tokens, t_parsed_scene *scene, char **err);
bool		safe_parse_light(char **tokens, t_parsed_scene *scene, char **err);
bool		safe_parse_camera(char **tokens, t_parsed_scene *scene, char **err);
bool		safe_parse_sphere(char **tok, t_parsed_object *o, char **err);
bool		safe_parse_plane(char **tok, t_parsed_object *o, char **err);
bool		safe_parse_cylinder(char **tok, t_parsed_object *o, char **err);
bool		dispatch_tokens(char **tok, t_parsed_scene *scene, char **err);
t_scene		build_runtime_scene(const t_parsed_scene *p);
t_scene		build_runtime_scene_safe(const t_parsed_scene *p,
				t_parsed_scene *to_cleanup);
void		init_cylinders(t_scene *dst, const t_parsed_scene *p);
void		init_planes(t_scene *dst, const t_parsed_scene *p);
void		init_elements(t_scene *dst, const t_parsed_scene *p);

#endif
