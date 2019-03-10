/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_highlvl_graphics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 13:35:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 18:54:51 by sgalasso         ###   ########.fr       */
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

void			draw_line(t_data *data, t_vec vec,
				Uint32 color, t_limit *limit)
{
	int e2;
	int tab[5];

	bresenham_tab(tab, vec.p1, vec.p2);
	while (!((int)vec.p1.x == (int)vec.p2.x && (int)vec.p1.y == (int)vec.p2.y))
	{
		if (!limit || ((int)vec.p1.x > limit->l && (int)vec.p1.x < limit->r
		&& (int)vec.p1.y > limit->t && (int)vec.p1.y < limit->b))
			ft_setpixel(data->surface, (int)vec.p1.x, (int)vec.p1.y, color);
		e2 = tab[4];
		if (e2 > -tab[0] && (int)vec.p1.x != (int)vec.p2.x)
		{
			tab[4] -= tab[2];
			vec.p1.x = (int)vec.p1.x + tab[1];
		}
		if (e2 < tab[2] && (int)vec.p1.y != (int)vec.p2.y)
		{
			tab[4] += tab[0];
			vec.p1.y = (int)vec.p1.y + tab[3];
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
	t_vec vec1;
	t_vec vec2;
	t_vec vec3;
	t_vec vec4;

	vec1 = (t_vec){(t_pos){rect.x, rect.y}, (t_pos){rect.x + rect.w, rect.y}};
	vec2 = (t_vec){(t_pos){rect.x, rect.y}, (t_pos){rect.x, rect.y + rect.h}};
	vec3 = (t_vec){(t_pos){rect.x + rect.w, rect.y},
	(t_pos){rect.x + rect.w, rect.y + rect.h}};
	vec4 = (t_vec){(t_pos){rect.x, rect.y + rect.h},
	(t_pos){rect.x + rect.w, rect.y + rect.h}};
	draw_line(data, vec1, color, 0);
	draw_line(data, vec2, color, 0);
	draw_line(data, vec3, color, 0);
	draw_line(data, vec4, color, 0);
}
