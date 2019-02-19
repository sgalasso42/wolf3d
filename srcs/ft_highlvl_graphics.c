/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_highlvl_graphics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 13:35:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 14:29:07 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Color		ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

static void		bresenham_tab(int *tab, t_pos p1, t_pos p2)
{
	tab[0] = abs((int)p2.x - (int)p1.x);
	tab[1] = (int)p1.x < (int)p2.x ? 1 : -1;
	tab[2] = abs((int)p2.y - (int)p1.y);
	tab[3] = (int)p1.y < (int)p2.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) / 2;
}

void			draw_line(t_data *data, t_pos p1, t_pos p2,
				Uint32 color, t_limit *limit)
{
	int e2;
	int tab[5];

	bresenham_tab(tab, p1, p2);
	while (!((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y))
	{
		if (!limit || ((int)p1.x > limit->l && (int)p1.x < limit->r
		&& (int)p1.y > limit->t && (int)p1.y < limit->b))
			ft_setpixel(data->surface, (int)p1.x, (int)p1.y, color);
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

void			ft_draw_rect(SDL_Rect rect, Uint32 color,
				t_limit *limit, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < rect.h)
	{
		j = 0;
		while (j < rect.w)
		{
			if (!limit || (rect.x + j > limit->l && rect.x + j < limit->r
			&& rect.y + i > limit->t && rect.y + i < limit->b))
				ft_setpixel(data->surface, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}

void			ft_draw_border(SDL_Rect rect, Uint32 color, t_data *data)
{
	t_pos p1;
	t_pos p2;
	t_pos p3;
	t_pos p4;

	p1 = (t_pos){rect.x, rect.y};
	p2 = (t_pos){rect.x + rect.w, rect.y};
	p3 = (t_pos){rect.x, rect.y + rect.h};
	p4 = (t_pos){rect.x + rect.w, rect.y + rect.h};
	draw_line(data, p1, p2, color, 0);
	draw_line(data, p1, p3, color, 0);
	draw_line(data, p2, p4, color, 0);
	draw_line(data, p3, p4, color, 0);
}
