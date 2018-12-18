/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:00:12 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 12:33:35 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_draw_rect(int x, int y, int w, int h,
		int r, int g, int b, t_limit limit, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (x + j > limit.l && x + j < limit.r
			&& y + i > limit.t && y + i < limit.b)
			{
				SDL_SetRenderDrawColor(data->sdl.renderer, r, g, b, 255);
				SDL_RenderDrawPoint(data->sdl.renderer, x + j, y + i);
			}
			j++;
		}
		i++;
	}
}

void	ft_minimap(t_data *data)
{
	t_limit	limit;
	t_size	map_size; // calculee
	t_pos	pos_play; // calculee
	t_pos	centre;
	t_pos	diff;
	int		size = 30;
	int		i;
	int		j;

	centre.x = (WIN_W - (size * data->map_sz.w) / 2);
	centre.y = size * data->map_sz.h / 2;
	map_size.w = size * data->map_sz.w;
	map_size.h = size * data->map_sz.h;
	pos_play.x = data->player.position.x * size;
	pos_play.y = data->player.position.y * size;
	diff.x = centre.x - pos_play.x;
	diff.y = centre.y - pos_play.y;
	limit.l = WIN_W - map_size.w;
	limit.r = WIN_W;
	limit.t = 0;
	limit.b = map_size.h;

	// border
	ft_draw_rect(WIN_W - map_size.w, 0,
	map_size.w, map_size.h, 255, 0, 0, limit, data);

	// background
	ft_draw_rect(diff.x, diff.y, map_size.w, map_size.h, 255, 255, 255, limit, data);

	// walls
	i = 0;
	while (i < data->map_sz.h)
	{
		j = 0;
		while (j < data->map_sz.w)
		{
			if (data->map[i][j] == 1)
				ft_draw_rect(diff.x + (j * size), diff.y + (i * size),
				size, size, 0, 0, 255, limit, data);
			j++;
		}
		i++;
	}

	// player
	double	rayon = 25;
	double	angle;
	double	step_x;
	double	step_y;

	// angle en radian
	angle = (data->player.direction - 30) * M_PI / 180;
	step_x = -cos(angle) * rayon;
	step_y = -sin(angle) * rayon;

	SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);

	SDL_RenderDrawLine(data->sdl.renderer,
	centre.x, centre.y,
	centre.x + step_x, centre.y + step_y);

	angle = (data->player.direction + 30) * M_PI / 180;
	step_x = -cos(angle) * rayon;
	step_y = -sin(angle) * rayon;

	SDL_RenderDrawLine(data->sdl.renderer,
	centre.x, centre.y,
	centre.x + step_x, centre.y + step_y);

	SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
}
