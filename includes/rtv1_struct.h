/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 14:11:14 by igomez            #+#    #+#             */
/*   Updated: 2016/06/21 19:56:46 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# define ANG_PLANE_X				M_DIR(0 , M_PI_2, 0);
# define ANG_PLANE_Y				M_DIR(-M_PI_2, 0, 0);
# define ANG_PLANE_Z				M_DIR(0, 0, 0)

# define PARAM_OBJ(TYPE, C, A, D, SP, SH)	(t_obj_param){TYPE, C, A, D, SP, SH}
# define PARAM_SPOT(D, SP)					(t_spot_param){D, SP}

# define PARAM_OBJ_DEFAULT(TYPE, C)		PARAM_OBJ(TYPE, C, 0.1, 0.8, 0.8, 50)
# define PARAM_SPOT_DEFAULT				PARAM_SPOT(0.6, 1)

# include "libft.h"
# include "rtv1_matrix.h"
# include <stdint.h>

/*
** OBJECTS: Types
*/

# define OBJ_NUMBER		(4)

typedef enum		e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}					t_obj_type;

/*
** Post Processing type
*/
# define PROCESS_NB		(9)

typedef enum		e_process_type
{
	NONE = 0,
	GRAY,
	SHADE,
	GAMMA,
	CONTRAST,
	BRIGHT,
	INVERSE,
	NEAREST_256,
	NEAREST_16,
	SEPIA,
	ALL,
}					t_process_type;

/*
** OBJECTS: Parameters
** + Type
** + Color
** + Ambiant
** + Diffuse
** + Specular (shininess)
** + Shininess (attenuation)
*/

typedef struct		s_obj_param
{
	t_obj_type		type;
	int				color;
	double			ambiant;
	double			diffuse;
	double			specular;
	double			shininess;
	bool			negatif;
	double			reflection;
	double			refraction;
	double			transparancy;
}					t_obj_param;

/*
** OBJECT: Structure
**	- A position (x, y, z)
**	- Three rotations (resp. along the axis Ox, Oy, and Oz)
**	- A setup matrix (to move camera to the right position)
**	- A cleanup matrix (to restore the camera initial position)
**	- Parameters of the object (type, maths, ...)
*/

typedef struct		s_obj
{
	int				n;
	t_matrix		position;
	t_matrix		ang;
	t_matrix		scale;
	t_matrix		setup;
	t_matrix		cleanup;
	t_obj_param		param;
}					t_obj;

/*
** CAMERA:
** + Position
** + Direction
*/

typedef struct		s_cam
{
	int				n;
	t_matrix		position;
	t_matrix		ang;
	t_matrix		setup;
}					t_cam;

/*
** SPOTLIGHT: Parameters
** + Diffuse
** + Specular (shininess)
*/

typedef struct		s_spot_param
{
	double			diffuse;
	double			specular;
	int				color;
}					t_spot_param;

/*
** SPOTLIGHT:
** + Position
** + Parameters
*/

typedef struct		s_spot
{
	int				n;
	t_matrix		position;
	t_spot_param	param;
}					t_spot;

/*
** SCENE:
**	- One camera (Bonus: one window per camera ?)
**	- A list of objects (eventually null)
**	- A list of spots (eventually null)
*/

typedef struct		s_scene
{
	t_list			*actual_cam;
	t_list			*cam;
	t_list			*obj;
	t_list			*spot;
}					t_scene;

/*
** Struct: Functions
*/

t_scene				*new_scene(void);
t_obj				*new_obj(void);
t_spot				*new_spot(void);

/*
** RAY:
**	- Start position
**	- Direction
**	- A pointer to the intersected object if any (else NULL)
**	- Intersection point if any
**	- Normal at intersection if any
*/

typedef struct     s_neg
{
	double front;
	double back;
	struct s_neg  *next;
}					t_neg;

typedef struct		s_ray
{
	t_matrix		start;
	t_matrix		dir;
	t_obj			*obj;
	double			dist;
	t_matrix		intersection;
	t_matrix		normal;
	double			front;
	double			back;
	t_neg			*neg;
	t_list			*lst_obj;
}					t_ray;

/*
** Ray: functions
*/

int					ray_intersect_sphere(t_ray *ray, t_obj *obj);
int					ray_intersect_plane(t_ray *ray, t_obj *obj);
int					ray_intersect_cone(t_ray *ray, t_obj *obj);
int					ray_intersect_cylinder(t_ray *ray, t_obj *obj);
double				solve_2_degree_neg(double a, double b,
					double c, t_ray *ray);
double		solved(double a, double b, double c, t_ray *ray);
int				sphere_neg(t_ray *ray);
int				plane_neg(t_ray *ray);
int				cylinder_neg(t_ray *ray);
int				cone_neg(t_ray *ray);



/*
** Post processing
*/
typedef struct		s_ucolor
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_ucolor;

typedef struct		s_fcolor
{
	float			r;
	float			g;
	float			b;
}					t_fcolor;

#endif
