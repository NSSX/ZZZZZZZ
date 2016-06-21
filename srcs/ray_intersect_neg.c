#include "rtv1.h"
#include <math.h>
#include <stdio.h>

double		solve_2_degree_neg(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;

	if (fabs(a) < ERROR)
	{
		if (fabs(b) < ERROR)
			return (-1);
		res = -c / b;
	}
	else
	{
		tmp = b * b - 4 * a * c;
		if (tmp < 0)
			return (-1);
		tmp = sqrt(tmp);
		double front = (-b - tmp) / (2 * a);
		double back = (-b + tmp) / (2 * a);

			t_neg *neg;

			neg = ray->neg;
			while(neg)
			{
				ray->front = neg->front;
				ray->back = neg->back;
			if(front >= ray->front && front <= ray->back)
				{
					if(back >= ray->front && back <= ray->back)
						return(-1);
					return(back);
				}
				if(front < 0)
				{
					if(back >= ray->front && back < ray->back)
						return(-1);
				}
				neg = neg->next;
			}
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}


double		solved(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;

	ray->front = 10000;
	ray->back = 10000;
	if (fabs(a) < ERROR)
	{
		if (fabs(b) < ERROR)
			return (-1);
		res = -c / b;
	}
	else
	{
		tmp = b * b - 4 * a * c;
		if (tmp < 0)
			return (-1);
		tmp = sqrt(tmp);
		ray->front = (-b - tmp) / (2 * a);
		ray->back = (-b + tmp) / (2 * a);
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}

int				sphere_neg(t_ray *ray)
{
	double a;
	double b;
	double c;

	a =   M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0)
		+ M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->dir), 2, 0);
	b =   2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0)
		+ 2 * M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->start), 2, 0);
	c =   M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		+ M_IJ(&(ray->start), 2, 0) * M_IJ(&(ray->start), 2, 0)
		- 1;
	ray->dist = solved(a,b,c,ray);
    return(0);
}

int				plane_neg(t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = 0;
	b = M_IJ(&(ray->dir), 2, 0);
	c = M_IJ(&(ray->start), 2, 0);
	ray->dist = solved(a, b, c,ray);
    return(0);
}

int				cylinder_neg(t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0);
	b = 2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0);
	c = M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- 1;
	ray->dist = solved(a, b, c,ray);
    return(0);
}

int				cone_neg(t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0)
		- M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->dir), 2, 0);
	b = 2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- 2 * M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->start), 2, 0);
	c = M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- M_IJ(&(ray->start), 2, 0) * M_IJ(&(ray->start), 2, 0);
	ray->dist = solved(a, b, c,ray);
    return(0);
}
