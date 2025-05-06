/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:58:21 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:15:49 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

// ---- temp ------
# include <string.h>

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef struct s_Vec3
{
	double			x;
	double			y;
	double			z;
}					t_Vec3;

typedef struct s_Ray
{
	t_Vec3			origin;
	t_Vec3			direction;
}					t_Ray;

typedef struct s_AmbiantLight
{
	double			ratio;
	t_Vec3			color;
}					t_AmbientLight;

typedef struct s_Camera
{
	t_Vec3			position;
	t_Vec3			orientation;
	double			fov;
}					t_Camera;

typedef struct s_Light
{
	t_Vec3			position;
	double			intensity;
	t_Vec3			color;
}					t_Light;

typedef struct s_Sphere
{
	t_Vec3			center;
	double			radius;
	t_Vec3			color;
}					t_Sphere;

typedef struct s_Plane
{
	t_Vec3			normal;
	t_Vec3			center;
	t_Vec3			color;
}					t_Plane;

typedef struct s_Cylinder
{
	t_Vec3			position;
	t_Vec3			axis;
	double			diameter;
	double			height;
	t_Vec3			color;
}					t_Cylinder;

typedef struct s_Scene
{
	t_Camera		camera;
	t_AmbientLight	ambient;
	t_Light			*lights;
	int				light_count;
	t_Sphere		*spheres;
	int				sphere_count;
	t_Plane			*planes;
	int				plane_count;
	t_Cylinder		*cylinders;
	int				cylinder_count;
	t_mlx			mlx;
}					t_Scene;

typedef struct s_Intersection
{
	double			a;
	double			b;
	double			c;
	double			t0;
	double			t1;
	double			discriminant;
	double			closest_t;
	t_Vec3			intersection_point;
	t_Vec3			normal;
	t_Vec3			color;
}					t_Intersection;

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// -------- UTILS --------
float				ft_strtof(const char *str, char **endptr);

// -------- PARSING --------
void				parse_ambient_light(char *line, t_Scene *scene);
void				parse_camera(char *line, t_Scene *scene);
void				parse_sphere(char *line, t_Scene *scene);
void				parse_plane(char *line, t_Scene *scene);
int					parse_vector3(char **token, t_Vec3 *vector,
						const char *vector_name);
void				parse_light(char *line, t_Scene *scene);
int					parse_light_identifier(char **token);
int					add_light_to_scene(t_Scene *scene, t_Light *new_light);
int					parse_color_component(char **token, double *component,
						const char *component_name);
void				parse_cylinder(char *line, t_Scene *scene);
void				add_cylinder_to_scene(t_Scene *scene, t_Cylinder *cylinder);

// -------- PARSING UTILS --
void				free_tokens(char **tokens);
int					parse_double(char *str, double *value);
char				**ft_split_whitespace(const char *str);
int					parse_color(char *str, int *r, int *g, int *b);
char				**ft_split(const char *str, char delim);
int					count_tokens(char **tokens);
long int			ft_strtol(const char *nptr, char **endptr, int base);
char				*ft_strtok(char *str, const char *delim);
double				ft_strtod(const char *nptr, char **endptr);
int					ft_strcmp(const char *s1, const char *s2);

// -------- INIT ---------
void				init_scene(t_Scene *scene);
void				start_window(t_Scene *scene);

// -------- KEY BINDING --
int					close_window(t_Scene *scene);
int					key_hook(int keycode, t_Scene *scene);

// -------- RENDER SCENE --
void				render_scene(t_Scene *scene);

// -------- RAYS ----------
t_Ray				generate_ray(int x, int y, t_Scene *scene);
t_Vec3				trace_ray(t_Ray ray, t_Scene *scene);

// -------- CHECK INTERSECTIONS --
double				check_sphere_intersection(t_Ray ray, t_Scene *scene,
						t_Intersection *intersection);
double				check_plane_intersection(t_Ray ray, t_Scene *scene,
						t_Intersection *intersection);
double				check_cylinder_intersection(t_Ray ray, t_Scene *scene,
						t_Intersection *intersection);

// -------- RAYS UTILS ----
t_Vec3				normalize(t_Vec3 v);
t_Vec3				scalar_mult(t_Vec3 v, double scalar);
t_Vec3				cross(t_Vec3 v1, t_Vec3 v2);
double				dot(t_Vec3 v1, t_Vec3 v2);

// -------- VECTOR UTILS --
t_Vec3				add_vectors(t_Vec3 v1, t_Vec3 v2);
double				vector_length(t_Vec3 v);
t_Vec3				vector_sub(t_Vec3 v1, t_Vec3 v2);

// -------- INTERSECT -----
double				intersect_ray_with_sphere(t_Ray ray, t_Sphere *sphere);
double				intersect_ray_with_plane(t_Ray ray, t_Plane *plane);
int					intersect_ray_with_cylinder(t_Ray ray, t_Cylinder *cylinder,
						double *t);
int					intersect_ray_with_objects(t_Ray ray, t_Scene *scene,
						double max_dist);

// -------- LIGHTING ------
t_Vec3				apply_ambient_light(t_Vec3 object_color,
						t_AmbientLight ambient);
t_Vec3				apply_diffuse_light(t_Vec3 object_color, t_Light light,
						t_Vec3 intersection_point, t_Vec3 normal);
int					is_in_shadow(t_Scene *scene, t_Vec3 intersection_point,
						t_Light light);

#endif