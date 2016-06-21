/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:17:05 by igomez            #+#    #+#             */
/*   Updated: 2016/06/18 21:58:37 by igomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx_encoding.h"
#include "mlx.h"

int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->screen->img, 0, 0);
	return (0);
}

int		loop_hook(t_env *e)
{
	if (FLAG_GET(e->flag, MASK_RECALC))
	{
		recalc_scene(e);
		if (e->post_process_type != 0)
			ft_post_processing(e);
		ft_printelapsed(e);
		FLAG_UNSET(e->flag, MASK_RECALC);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->screen->img, 0, 0);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	t_list *it;

	if (keycode == KEYCODE_ESCAPE)
		ft_exit(0, e);
	if (keycode == KEYCODE_DELETE)
		ft_build_bmp(e);
	if (keycode == KEYCODE_RIGHT)
	{
		e->scene->actual_cam = e->scene->actual_cam->next;
		if (e->scene->actual_cam == 0)
			e->scene->actual_cam = e->scene->cam;
		e->flag = MASK_RECALC;
	}
	if (keycode == KEYCODE_LEFT)
	{
		if (e->scene->actual_cam == e->scene->cam)
			e->scene->actual_cam = 0;
		it = e->scene->cam;
		while (it->next != e->scene->actual_cam)
			it = it->next;
		e->scene->actual_cam = it;
		e->flag = MASK_RECALC;
	}
	return (0);
}
