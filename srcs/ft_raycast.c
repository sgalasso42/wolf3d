/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:17:24 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 17:45:59 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_is_inwall(t_pos *pos, t_data *data)
{
	int		x2;
	int		y2;

	x2 = pos->x / BLOC_SIZE;
	y2 = pos->y / BLOC_SIZE;
	if (x2 < 0 || x2 >= data->map_sz.w || y2 < 0 || y2 >= data->map_sz.h)
		return (0);
	if (data->map[y2][x2] == 1 || data->map[y2][x2] == 3)
		return (1);
	return (0);
}

static void		ft_get_raydata(t_pos pos,
				double alpha_r, int i, t_thread *thread)
{
	t_pos	player_pos;
	double	distance_x;
	double	distance_y;

	player_pos.x = thread->data->player.position.x * BLOC_SIZE;
	player_pos.y = thread->data->player.position.y * BLOC_SIZE;
	distance_x = (thread->ray[i].axis == 1)
	? pos.x - player_pos.x : (int)pos.x - player_pos.x;
	distance_y = (thread->ray[i].axis == 1)
	? (int)pos.y - player_pos.y : pos.y - player_pos.y;
	thread->ray[i].dist_minimap = ft_pythagore(distance_x, distance_y);
	thread->ray[i].distance = thread->ray[i].dist_minimap * cos(alpha_r);
	thread->ray[i].x = pos.x * 8;
	thread->ray[i].y = pos.y * 8;
}

static int		ft_iterate_ray(int i, t_pos *pos, t_thread *thread)
{
	double	angle_r;
	double	alpha_r;

	alpha_r = (fabs(thread->data->player.direction
	- thread->ray[i].angle_d)) * M_PI / 180;
	angle_r = thread->ray[i].angle_d * M_PI / 180;
	if ((ft_is_inwall(pos, thread->data)) == 1)
	{
		thread->ray[i].axis = 1;
		ft_get_raydata(*pos, alpha_r, i, thread);
		return (0);
	}
	pos->x += -cos(angle_r) * 1;
	if ((ft_is_inwall(pos, thread->data)) == 1)
	{
		thread->ray[i].axis = 2;
		ft_get_raydata(*pos, alpha_r, i, thread);
		return (0);
	}
	pos->y += -sin(angle_r) * 1;
	return (1);
}

void			ft_calc_distance(int i, int x, t_thread *thread)
{
	t_pos	pos;

	thread->ray[i].angle_d =
	(thread->data->player.direction - 30) + (x * (60.0 / WIN_W));
	pos.x = thread->data->player.position.x * BLOC_SIZE;
	pos.y = thread->data->player.position.y * BLOC_SIZE;
	while (pos.x > 0 && pos.x < thread->data->map_sz.w * BLOC_SIZE
	&& pos.y > 0 && pos.y < thread->data->map_sz.h * BLOC_SIZE)
	{
		if (!ft_iterate_ray(i, &pos, thread))
			return ;
	}
	thread->ray[i].distance = -1;
}
