/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:00:12 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 17:29:04 by jsauron          ###   ########.fr       */
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
				SDL_SetRenderDrawColor(data->sdl.renderer, r, g, b, 180);
				SDL_RenderDrawPoint(data->sdl.renderer, x + j, y + i);
			}
			j++;
		}
		i++;
	}
}

void	bresenham_tab(int *tab, t_pos p1, t_pos p2)
{
	tab[0]	 = abs((int)p2.x - (int)p1.x);
	tab[1] = (int)p1.x < (int)p2.x ? 1 : -1;
	tab[2] = abs((int)p2.y - (int)p1.y);
	tab[3] = (int)p1.y < (int)p2.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) / 2;
}

void	draw_line(t_data *data, t_pos p1, t_pos p2, int r, int g, int b)
{
	int e2;
	int tab[5];

	bresenham_tab(tab, p1, p2);
	while (!((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y))
	{
		SDL_SetRenderDrawColor(data->sdl.renderer, r, g, b, 255);
		SDL_RenderDrawPoint(data->sdl.renderer, (int)p1.x, (int)p1.y);
		e2 = tab[4];
		if (e2 > -tab[0] && (int)p1.x != (int)p2.x)
		{
			tab[4] -= tab[2];
			p1.x = (int)p1.x + tab[1];
		}
		if (e2 < tab[2] && (int)p1.y != (int)p2.y)
		{
			tab[4] += tab[0];
			p1.y = (int)p1.y + tab[3];
		}
	}
}

void	ft_draw_border(t_data *data, int x, int y)
{
	t_pos p1;
	t_pos p2;
	t_pos p3;
	t_pos p4;

	p1.x = x + 0;
	p1.y = y + 0;
	p2.x = x + (WIN_W / 4);
	p2.y = y + 0;
	p3.x = x + 0;
	p3.y = y + (WIN_H / 4);
	p4.x = x + (WIN_W / 4);
	p4.y = y + (WIN_H / 4);

	draw_line(data, p1, p2, 255, 255, 255);
	draw_line(data, p1, p3, 255, 255, 255);
	draw_line(data, p2, p4, 255, 255, 255);
	draw_line(data, p3, p4, 255, 255, 255);
}

void	ft_minimap(t_data *data)
{
	t_limit	limit;
	t_size	map_size; // calculee
	t_pos	pos_play; // calculee
	t_pos	centre;
	t_pos	diff;
	int		i;
	int		j;

	centre.x = (WIN_W - (WIN_W / 4) / 2);
	centre.y = (WIN_H / 4) / 2;
	map_size.w = data->mnp_size * data->map_sz.w;
	map_size.h = data->mnp_size * data->map_sz.h;
	pos_play.x = data->player.position.x * data->mnp_size;
	pos_play.y = data->player.position.y * data->mnp_size;
	diff.x = centre.x - pos_play.x;
	diff.y = centre.y - pos_play.y;
	limit.l = WIN_W - (WIN_W /4);
	limit.r = WIN_W;
	limit.t = 0;
	limit.b = (WIN_H / 4);

	//border rect
	ft_draw_border(data, WIN_W - (WIN_W / 4), 0);

	// border
	ft_draw_rect(WIN_W - map_size.w, 0,
			map_size.w, map_size.h, 0, 0, 0, limit, data);

	// background
	ft_draw_rect(diff.x, diff.y, map_size.w, map_size.h, 250, 250, 250, limit, data);

	// walls
	i = 0;
	while (i < data->map_sz.h)
	{
		j = 0;
		while (j < data->map_sz.w)
		{
			if (data->map[i][j] == 1)
				ft_draw_rect(diff.x + (j * data->mnp_size), diff.y + (i * data->mnp_size),
						data->mnp_size, data->mnp_size, 36, 68, 92, limit, data);
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
