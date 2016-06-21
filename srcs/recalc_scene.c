/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalc_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 17:48:56 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 05:49:43 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define WIN_X	(WIN_WIDTH / 2)
#define WIN_Y	(WIN_HEIGHT / 2)

int		recalc_scene(t_env *e)
{
	int		x;
	int		y;
	t_ray	ray;

	y = 0;
	e->c_old = clock();
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray.start = M_POINT(0, 0, 0);
			ray.dir = M_DIR(DIST_TO_PROJ, WIN_X - x, WIN_Y - y);
			mat_normalize(&(ray.dir));
			ray_setup_camera(&ray, (t_cam *)e->scene->actual_cam->content);
			ray_intersect(&ray, e);
			ft_draw_pix(TPIX(x, y, ray_color(&ray, e)), e->screen);
			++x;
		}
		++y;
	}
	e->c_new = clock();
	return (0);
}
