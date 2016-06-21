/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 01:22:32 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const t_key_value g_key_value[] =
{
	{"CONE", CONE},
	{"PLANE", PLANE},
	{"SPHERE", SPHERE},
	{"CYLINDER", CYLINDER},
	{0, 0}
};

int	ft_obj_parse_type(t_obj *obj, char const *line, size_t *count)
{
	size_t i;

	i = 0;
	while (g_key_value[i].key != 0)
	{
		if (ft_strstr(line, g_key_value[i].key) != 0)
		{
			obj->param.type = g_key_value[i].value;
			return (P_TYPE);
		}
		++i;
	}
	P_ERROR("TYPE", *count);
	obj->param.type = SPHERE;
	return (0);
}
