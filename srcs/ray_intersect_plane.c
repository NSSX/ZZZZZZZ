/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:07:43 by igomez            #+#    #+#             */
/*   Updated: 2016/06/21 20:27:47 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		ray_solution_plane(t_ray *ray, t_obj *obj)
{
	int		sign;

	ray->obj = obj;
	ray->intersection = M_POINT(
		M_IJ(&(ray->start), 0, 0) + ray->dist * M_IJ(&(ray->dir), 0, 0),
		M_IJ(&(ray->start), 1, 0) + ray->dist * M_IJ(&(ray->dir), 1, 0),
		M_IJ(&(ray->start), 2, 0) + ray->dist * M_IJ(&(ray->dir), 2, 0));
	if (M_IJ(&(ray->dir), 2, 0) < 0)
		sign = 1;
	else
		sign = -1;
	ray->normal = M_DIR(0, 0, sign);
	return (0);
}

double		solve_2_degree_neg_plane(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;

	if (fabs(a) < ERROR)
	{
		if (fabs(b) < ERROR)
			return (-1);
		res = -c / b;
		t_neg *neg;

		neg = ray->neg;
		while(neg)
		{
			ray->front = neg->front;
			ray->back = neg->back;
			if(res >= ray->front && res <= ray->back)
				return(-1);
			neg = neg->next;
		}
	}
	else
	{
		tmp = b * b - 4 * a * c;
		if (tmp < 0)
			return (-1);
		tmp = sqrt(tmp);
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}

int				ray_intersect_plane(t_ray *ray, t_obj *obj)
{
	double		a;
	double		b;
	double		c;

	a = 0;
	b = M_IJ(&(ray->dir), 2, 0);
	c = M_IJ(&(ray->start), 2, 0);
	//ray->dist = solve_2_degree(a, b, c);
	ray->dist = solve_2_degree_neg_plane(a, b, c,ray);
	if (ray->dist > 0)
		ray_solution_plane(ray, obj);
	return (0);
}
