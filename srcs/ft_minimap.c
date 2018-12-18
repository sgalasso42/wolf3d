/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:00:12 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 20:54:26 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_minimap(t_data *data)
{
	t_pos	origin;
	t_limit	limit;
	t_size	map_size; // calculee
	t_pos	pos_play; // calculee
	t_pos	centre;
	t_pos	diff;
	int		i;
	int		j;

	origin.x = WIN_W - (WIN_W / 4) - 10;
	origin.y = 10;
	centre.x = (WIN_W - (WIN_W / 4) / 2) - 10;
	centre.y = (WIN_H / 4) / 2 + 10;
	map_size.w = data->mnp_size * data->map_sz.w;
	map_size.h = data->mnp_size * data->map_sz.h;
	pos_play.x = data->player.position.x * data->mnp_size;
	pos_play.y = data->player.position.y * data->mnp_size;
	diff.x = centre.x - pos_play.x;
	diff.y = centre.y - pos_play.y;
	limit.l = origin.x;
	limit.r = WIN_W - origin.y;
	limit.t = 10;
	limit.b = WIN_H / 4 + 10;

	// border rect
	ft_draw_border(data, origin.x, origin.y);

	// border
	ft_draw_rect(WIN_W - map_size.w - 10, 10,
	map_size.w, map_size.h, 0xFF000000, &limit, data);

	// background
	ft_draw_rect(diff.x, diff.y, map_size.w, map_size.h, 0xFFADADAD, &limit, data);

	// walls
	i = 0;
	while (i < data->map_sz.h)
	{
		j = 0;
		while (j < data->map_sz.w)
		{
			if (data->map[i][j] == 1)
				ft_draw_rect(
				diff.x + (j * data->mnp_size),
				diff.y + (i * data->mnp_size),
				data->mnp_size, data->mnp_size,
				0xFF5C4424, &limit, data);
			j++;
		}
		i++;
	}

	// player
	double	angle;
	double	step_x;
	double	step_y;
	t_pos	a;
	t_pos	b;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < WIN_W / 8)
		{
			// angle en radian
			angle = (data->thread[i].ray[j].angle_d) * M_PI / 180;

			step_x = -cos(angle) * (data->thread[i].ray[j].dist_minimap)
			* data->mnp_size / 50;
			step_y = -sin(angle) * (data->thread[i].ray[j].dist_minimap)
			* data->mnp_size / 50;

			a.x = centre.x;
			a.y = centre.y;
			b.x = centre.x + step_x;
			b.y = centre.y + step_y;

			draw_line(data, a, b, 0xFFBFFCFF, &limit);
			j++;
		}
		i++;
	}
	// player
	ft_draw_rect(centre.x - 5, centre.y - 5, 10, 10, 0x0, 0, data);
}
