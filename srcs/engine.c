/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 16:29:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 05:43:22 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx.h"

int	ft_engine(int ac, char **av)
{
	t_env		e;

	if (env_mlx_init(&e) >= 0)
	{
		if ((e.scene = new_scene()) != 0)
		{
			if (env_parse_scene(&e, ac, av) == true)
			{
				FLAG_SET(e.flag, MASK_RECALC);
				mlx_loop(e.mlx);
			}
		}
	}
	ft_exit(0, &e);
	return (0);
}
