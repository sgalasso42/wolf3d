/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 17:17:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_calc_walls(int i, int x, t_thread *thread)
{
	double	height;

	height = 0;
	ft_calc_distance(i, x, thread);
	if (thread->ray[i].distance >= 0)
		height = (BLOC_SIZE / thread->ray[i].distance) * DIST_SCREEN;
	thread->ray[i].wall_top = (WIN_H - height) / 2;
	thread->ray[i].wall_bot = WIN_H - ((WIN_H - height) / 2);
}

void			*ft_calc_frame(void *arg)
{
	t_thread	*thread;
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
			ft_assign_color(x, y, i, thread);
			y++;
		}
		x += 8;
	}
	pthread_exit(0);
}

void			ft_rc_wolfcalc(t_data *data)
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
