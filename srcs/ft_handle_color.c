/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:10:19 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 20:01:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		choose_texture(int i, t_thread *thread)
{
	if (thread->ray[i].axis == VERTICAL_HIT)
	{
		if ((thread->ray[i].angle_d >= 0 && thread->ray[i].angle_d <= 180)
		|| thread->ray[i].angle_d >= 360)
			return (0);
		else
			return (1);
	}
	if (thread->ray[i].angle_d >= 90 && thread->ray[i].angle_d <= 270)
		return (2);
	return (3);
	
}

static Uint32	ft_calc_col(int y, int i, t_thread *thread)
{
	double	h_wall;
	t_coef	textr;

	double	ywall;
	Uint32	color;
	double	h_txtr;
	double	w_txtr;
	int		txtr_index = choose_texture(i, thread);

	ywall = (y - thread->ray[i].wall_top);
	w_txtr = thread->data->object[txtr_index].img_srf->w;
	h_txtr = thread->data->object[txtr_index].img_srf->h;
	h_wall = thread->ray[i].wall_bot - thread->ray[i].wall_top;

	if (thread->ray[i].axis == VERTICAL_HIT)
	{
		textr.x = ((int)(thread->ray[i].x / 8) % BLOC_SIZE) * w_txtr / BLOC_SIZE;
	}
	else if (thread->ray[i].axis == HORIZONTAL_HIT)
	{
		textr.x = ((int)(thread->ray[i].y / 8) % BLOC_SIZE) * w_txtr / BLOC_SIZE;
	}
	
	textr.y = h_txtr * ywall / h_wall;

	color = ft_getpixel(thread->data->object[txtr_index].img_srf,
	textr.x, textr.y, thread->data) | 0xFF000000;
	return (color);
}

/*Uint32          ft_texturing(t_env *env, int y, int p1, int p2)
{
	Uint32      color;
	int         w_tex;
	int         h_tex;
	int         x_tex;
	int         y_tex;
	int         ywall;

	ywall = y - p1;
	w_tex = surface->w;
	h_tex = surface->h;
	if (env->ray.side == 2)
		x_tex = ((int)env->ray.pos.x % env->bloc_size) * w_tex / env->bloc_size;
	else
		x_tex = ((int)env->ray.pos.y % env->bloc_size) * w_tex / env->bloc_size;
	y_tex = ywall * h_tex / (p2 - p1);
	color = ft_getpixel(surface, x_tex, y_tex, env);
	return (color);
}*/

Uint32			ft_get_color2(int axis, int angle_d)
{
	Uint32		color;

	color = 0;
	if (axis == 1)
	{
		if ((angle_d >= 0 && angle_d <= 180) || angle_d >= 360)
			color = 0xFF5454E5;
		else
			color = 0xFF86D865;
	}
	else if (axis == 2)
	{
		if (angle_d >= 90 && angle_d <= 270)
			color = 0xFFD8815F;
		else
			color = 0xFF89EFFF;
	}
	return (color);
}

void			ft_assign_color(int x, int y, int i, t_thread *thread)
{
	Uint32		color;

	color = 0x0;
	if (y < thread->ray[i].wall_top)
		color = (thread->data->lightshade) ? 0xFF46463B : 0xFFFFFED6;
	else if (y >= thread->ray[i].wall_top && y <= thread->ray[i].wall_bot)
	{
		color = (thread->data->texturing) ? ft_calc_col(y, i, thread)
			: ft_get_color2(thread->ray[i].axis, thread->ray[i].angle_d);

		// lightshading
		if (thread->data->lightshade == 1)
			color = ft_light_shade(thread->ray[i].distance, color);
	}
	ft_setpixel(thread->data->surface, x, y, color);
}
