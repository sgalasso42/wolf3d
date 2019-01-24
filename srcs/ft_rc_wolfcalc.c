/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2019/01/24 16:13:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_is_inwall(t_pos *pos, t_data *data)
{
	int		x2;
	int		y2;

	x2 = pos->x / BLOC_SIZE;
	y2 = pos->y / BLOC_SIZE;
	if (data->map[y2][x2] == 1 || data->map[y2][x2] == 3)
		return (1);
	return (0);
}

void		ft_get_raydata(t_pos pos,
			t_pos player_pos, double alpha_r, int i, t_thread *thread)
{
	double	distance_x;
	double	distance_y;

	distance_x = (thread->ray[i].axis == 1)
	? pos.x - player_pos.x : (int)pos.x - player_pos.x;
	distance_y = (thread->ray[i].axis == 1)
	? (int)pos.y - player_pos.y : pos.y - player_pos.y;
	thread->ray[i].dist_minimap = ft_pythagore(distance_x, distance_y);
	thread->ray[i].distance = thread->ray[i].dist_minimap * cos(alpha_r);
	thread->ray[i].x = pos.x * 8;
	thread->ray[i].y = pos.y * 8;
}

void		ft_calc_distance(int i, int x, t_thread *thread)
{
	t_pos	player_pos;	// position calculee
	double	alpha_r;	// angle entre direction et ray
	double	angle_r;	// angle radian
	t_pos	pos;

	player_pos.x = thread->data->player.position.x * BLOC_SIZE;
	player_pos.y = thread->data->player.position.y * BLOC_SIZE;

	thread->ray[i].angle_d =
	(thread->data->player.direction - 30) + (x * (60.0 / WIN_W));

	angle_r = thread->ray[i].angle_d * M_PI / 180;
	alpha_r = (fabs(thread->data->player.direction
	- thread->ray[i].angle_d)) * M_PI / 180;

	pos.x = player_pos.x;
	pos.y = player_pos.y;
	while (pos.x > 0 && pos.x < thread->data->map_sz.w * BLOC_SIZE
	&& pos.y > 0 && pos.y < thread->data->map_sz.h * BLOC_SIZE)
	{
		if ((ft_is_inwall(&pos, thread->data)) == 1) // y
		{
			thread->ray[i].axis = 1;
			ft_get_raydata(pos, player_pos, alpha_r, i, thread);
			return ;
		}
		pos.x += -cos(angle_r) * 1;
		if ((ft_is_inwall(&pos, thread->data)) == 1) // x
		{
			thread->ray[i].axis = 2;
			ft_get_raydata(pos, player_pos, alpha_r, i, thread);
			return ;
		}
		pos.y += -sin(angle_r) * 1;
	}
	// out of map
	thread->ray[i].distance = -1;
}

void					ft_calc_walls(int i, int x, t_thread *thread)
{
	double	height;

	height = 0;
	ft_calc_distance(i, x, thread);
	if (thread->ray[i].distance >= 0)
		height = (BLOC_SIZE / thread->ray[i].distance) * DIST_SCREEN;
	thread->ray[i].wall_top = (WIN_H - height) / 2;
	thread->ray[i].wall_bot = WIN_H - ((WIN_H - height) / 2);
}

Uint32		ft_get_color(int axis, int angle_d, int x, int y, t_data *data)
{
	Uint32		color;

	color = 0;
	if (axis == 1)
	{
		if ((angle_d >= 0 && angle_d <= 180) || angle_d >= 360)
			color = ft_getpixel(data->object[0].img_srf, x, y, data);
		else
			color = ft_getpixel(data->object[1].img_srf, x, y, data);
	}
	else if (axis == 2)
	{
		if (angle_d >= 90 && angle_d <= 270)
			color = ft_getpixel(data->object[2].img_srf, x, y, data);
		else
			color = ft_getpixel(data->object[3].img_srf, x, y, data);
	}
	return (color | 0xFF000000);
}

Uint32		ft_get_color2(int axis, int angle_d)
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

Uint32					ft_calc_col(int y, int i, t_thread *thread)
{
	Uint32	color;
	double	y_pixel;
	double	h_textr;
	double	h_wall;
	int		y_textr;
	int		x_textr;

	y_pixel = (y - thread->ray[i].wall_top);
	h_textr = thread->data->object[0].img_srf->h;
	h_wall = thread->ray[i].wall_bot - thread->ray[i].wall_top;
	y_textr = h_textr * y_pixel / h_wall;
	if (thread->ray[i].axis == 1)
	{
		x_textr = (thread->ray[i].x) % (thread->data->object[0].img_srf->w);
		x_textr = (x_textr * thread->data->object[0].img_srf->w) / (BLOC_SIZE);
		x_textr /= 8;
	}
	else
		x_textr = (thread->ray[i].y) % (thread->data->object[0].img_srf->w);
	color = ft_get_color(thread->ray[i].axis,
	thread->ray[i].angle_d, x_textr, y_textr, thread->data);
	return (color);
}

void					*ft_calc_frame(void *arg)
{
	t_thread	*thread;
	Uint32		color;
	int			x;
	int			y;
	int			i;

	i = -1;
	thread = (t_thread *)arg;
	x = thread->x_start;
	while (x < WIN_W)
	{
		y = 0;
		ft_calc_walls(++i, x, thread);
		while (y < WIN_H)
		{
			color = 0x0;
			if (y < thread->ray[i].wall_top)
				color = (thread->data->lightshade) ? 0xFF46463B : 0xFFFFFED6;
			else if (y >= thread->ray[i].wall_top && y <= thread->ray[i].wall_bot)
			{
				color =  (thread->data->texturing) ? ft_calc_col(y, i, thread)
				: ft_get_color2(thread->ray[i].axis, thread->ray[i].angle_d);
				if (thread->data->lightshade == 1)
					color = ft_light_shade(thread->ray[i].distance, color);
			}
			ft_setpixel(thread->data->surface,
			x, (int)(y + thread->data->jump / (thread->ray[i].distance / 100)) % WIN_H, color);
			y++;
		}
		x += 8;
	}
	pthread_exit(0);
}

void				ft_rc_wolfcalc(t_data *data)
{
	int i;

	i = 0;
	data->surface = ft_new_surface(WIN_H, WIN_W, data);
	while (i < 8)
	{	
		data->thread[i].x_start = i;
		data->thread[i].data = data;
		ft_bzero(data->thread[i].ray, sizeof(t_ray) * (WIN_W / 8));
		if ((pthread_create(&(data->thread[i].th), NULL,
		ft_calc_frame, (void *)&(data->thread[i]))) != 0)
			ft_err_exit("wolf3d: error: pthread_create failed", data);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if ((pthread_join(data->thread[i++].th, 0)) != 0)
			ft_err_exit("wolf3d: error: pthread_create failed", data);
	}
}
