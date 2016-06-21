/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:00:28 by igomez            #+#    #+#             */
/*   Updated: 2016/06/21 20:30:34 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	(*g_intersect[OBJ_NUMBER])(t_ray *, t_obj *) =
{
	&ray_intersect_sphere,
	&ray_intersect_plane,
	&ray_intersect_cylinder,
	&ray_intersect_cone
};

static int	ray_iscloser(t_ray *ray_old, t_ray *ray_new)
{
	if (!ray_old->obj)
		return (1);
	if (ray_new->dist > 0 && ray_new->dist < ray_old->dist)
		return (1);
	return (0);
}

static int	ray_intersect_obj(t_ray *ray, t_obj *obj)
{
	if ((uint32_t)obj->param.type > OBJ_NUMBER)
		return (0);
	return (g_intersect[obj->param.type](ray, obj));
}

static int	(*g_intersect_neg[OBJ_NUMBER])(t_ray *) =
{
	&sphere_neg,
	&plane_neg,
	&cylinder_neg,
	&cone_neg
};

static int	intersect_obj_neg(t_ray *ray, t_obj *obj)
{
	if ((uint32_t)obj->param.type > OBJ_NUMBER)
		return (0);
	return (g_intersect_neg[obj->param.type](ray));
}

int			ray_intersect(t_ray *ray, t_env *e)
{
	t_list	*lst;
	t_ray	tmp;
	t_neg	*lst_neg;

	lst_neg = NULL;
	lst = e->scene->obj;
	ray->lst_obj = e->scene->obj;
	while (ray->lst_obj)
	{
		tmp = *ray;
		t_obj *ob;
		ob = ray->lst_obj->content;
		if(ob)
		{
			if(ob->param.negatif == true)
			{
				ray_setup_obj(&tmp, ray->lst_obj->content);
				intersect_obj_neg(&tmp, ray->lst_obj->content);
				ray->front = tmp.front;
				ray->back = tmp.back;
				t_neg *tmp;
				tmp = lst_neg;
				if(!tmp)
				{
					lst_neg = malloc(sizeof(t_neg));
					lst_neg->front = ray->front;
					lst_neg->back = ray->back;
					lst_neg->next = NULL;
				}
				else
				{
					while(tmp->next)
					{
						tmp = tmp->next;
					}
					t_neg *new;
					new = malloc(sizeof(t_neg));
					new->front = ray->front;
					new->back = ray->back;
					new->next = NULL;
					tmp->next = new;
				}
			}
		}
		ray->lst_obj = ray->lst_obj->next;
	}
	ray_cleanup_obj(ray, ray->obj);
ray->neg = lst_neg;
	while (lst)
	{
		double ok = 0;
		tmp = *ray;
		t_obj *ob;
		ob = lst->content;
		if(ob)
		{
			//IF l'objet est negatif
			if(ob->param.negatif == true)
				ok = 1;
		}
		if(ok == 0)
		{
			ray_setup_obj(&tmp, lst->content);
			ray_intersect_obj(&tmp, lst->content);
			if (tmp.obj && ray_iscloser(ray, &tmp))
			{
				ray->obj = tmp.obj;
				ray->dist = tmp.dist;
				ray->intersection = tmp.intersection;
				ray->normal = tmp.normal;
			}
		}
		lst = lst->next;
	}
	ray_cleanup_obj(ray, ray->obj);
	return (0);
}
