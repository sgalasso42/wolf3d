/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:00:12 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 14:01:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_init_minimap(t_data *data)
{
	data->minimap.origin.x = WIN_W - (WIN_W / 4) - 10;
	data->minimap.origin.y = 10;
	data->minimap.centre.x = (WIN_W - (WIN_W / 4) / 2) - 10;
	data->minimap.centre.y = (WIN_H / 4) / 2 + 10;
	data->minimap.map_size.w = data->minimap.mnp_size * data->map_sz.w;
	data->minimap.map_size.h = data->minimap.mnp_size * data->map_sz.h;
	data->minimap.pos_play.x = data->player.position.x * data->minimap.mnp_size;
	data->minimap.pos_play.y = data->player.position.y * data->minimap.mnp_size;
	data->minimap.diff.x = data->minimap.centre.x - data->minimap.pos_play.x;
	data->minimap.diff.y = data->minimap.centre.y - data->minimap.pos_play.y;
	data->minimap.limit.l = data->minimap.origin.x;
	data->minimap.limit.r = WIN_W - data->minimap.origin.y;
	data->minimap.limit.t = 10;
	data->minimap.limit.b = WIN_H / 4 + 10;
}

static void		ft_set_player(t_data *data)
{
	SDL_Rect	player;
	double	angle_r;
	double	step_x;
	double	step_y;
	int		i;
	int		j;
	t_pos	a;
	t_pos	b;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < WIN_W / 8)
		{
			angle_r = (data->thread[i].ray[j].angle_d) * M_PI / 180;

			step_x = -cos(angle_r) * (data->thread[i].ray[j].dist_minimap)
			* data->minimap.mnp_size / 50;
			step_y = -sin(angle_r) * (data->thread[i].ray[j].dist_minimap)
			* data->minimap.mnp_size / 50;

			a.x = data->minimap.centre.x;
			a.y = data->minimap.centre.y;
			b.x = data->minimap.centre.x + step_x;
			b.y = data->minimap.centre.y + step_y;

			draw_line(data, a, b, 0xFFBFFCFF, &(data->minimap.limit));
			j++;
		}
		i++;
	}
	player.x = data->minimap.centre.x - 5;
	player.y = data->minimap.centre.y - 5;
	player.w = 10;
	player.h = 10;
	ft_draw_rect(player, 0x0, 0, data);
}

void	ft_minimap(t_data *data)
{
	SDL_Rect	border;
	SDL_Rect	bloc;
	int		i;
	int		j;

	ft_init_minimap(data);

	border.x = data->minimap.origin.x;
	border.y = data->minimap.origin.y;
	border.w = WIN_W / 4;
	border.h = WIN_H / 4;

	// border rect
	ft_draw_border(border, 0xFFFFFF, data);

	// background
	ft_draw_rect(border, 0xFF000000, &(data->minimap.limit), data);

	// map
	i = 0;
	while (i < data->map_sz.h)
	{
		j = 0;
		while (j < data->map_sz.w)
		{
			bloc.x = data->minimap.diff.x + (j * data->minimap.mnp_size);
			bloc.y = data->minimap.diff.y + (i * data->minimap.mnp_size);
			bloc.w = data->minimap.mnp_size;
			bloc.h = data->minimap.mnp_size;
			if (data->map[i][j] == 1)
				ft_draw_rect(bloc, 0xFF5C4424, &(data->minimap.limit), data);
			else if (data->map[i][j] == 0 || data->map[i][j] == 2)
				ft_draw_rect(bloc, 0xFFADADAD, &(data->minimap.limit), data);
			j++;
		}
		i++;
	}
	ft_set_player(data);	
}
