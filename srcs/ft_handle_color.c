/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:10:19 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 17:38:32 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static Uint32	ft_calc_col(int y, int i, t_thread *thread)
{
	Uint32	color;
	double	y_pixel;
	double	h_textr;
	double	h_wall;
	t_coef	textr;

	y_pixel = (y - thread->ray[i].wall_top);
	h_textr = thread->data->object[0].img_srf->h;
	h_wall = thread->ray[i].wall_bot - thread->ray[i].wall_top;
	textr.y = h_textr * y_pixel / h_wall;
	if (thread->ray[i].axis == 1)
	{
		textr.x = (thread->ray[i].x) % (thread->data->object[0].img_srf->w);
		textr.x = (textr.x * thread->data->object[0].img_srf->w) / (BLOC_SIZE);
		textr.x /= 8;
	}
	else
		textr.x = (thread->ray[i].y) % (thread->data->object[0].img_srf->w);
	color = ft_get_color(thread->ray[i].axis,
	thread->ray[i].angle_d, textr, thread->data);
	return (color);
}

Uint32			ft_get_color(int axis, int angle_d, t_coef pos, t_data *data)
{
	Uint32		color;

	color = 0;
	if (axis == 1)
	{
		if ((angle_d >= 0 && angle_d <= 180) || angle_d >= 360)
			color = ft_getpixel(data->object[0].img_srf, pos.x, pos.y, data);
		else
			color = ft_getpixel(data->object[1].img_srf, pos.x, pos.y, data);
	}
	else if (axis == 2)
	{
		if (angle_d >= 90 && angle_d <= 270)
			color = ft_getpixel(data->object[2].img_srf, pos.x, pos.y, data);
		else
			color = ft_getpixel(data->object[3].img_srf, pos.x, pos.y, data);
	}
	return (color | 0xFF000000);
}

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
	else if (y >= thread->ray[i].wall_top
	&& y <= thread->ray[i].wall_bot)
	{
		color = (thread->data->texturing) ? ft_calc_col(y, i, thread)
		: ft_get_color2(thread->ray[i].axis, thread->ray[i].angle_d);
		if (thread->data->lightshade == 1)
			color = ft_light_shade(thread->ray[i].distance, color);
	}
	ft_setpixel(thread->data->surface, x, y, color);
}
