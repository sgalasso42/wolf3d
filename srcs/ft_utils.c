/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:56:50 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:16:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		bresenham_tab(int *tab, t_pos p1, t_pos p2)
{
	tab[0] = abs((int)p2.x - (int)p1.x);
	tab[1] = (int)p1.x < (int)p2.x ? 1 : -1;
	tab[2] = abs((int)p2.y - (int)p1.y);
	tab[3] = (int)p1.y < (int)p2.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) / 2;
}

void			draw_line(t_data *data, t_vec *vec,
				Uint32 color, t_limit *limit)
{
	int e2;
	int tab[5];

	bresenham_tab(tab, vec->a, vec->b);
	while (!((int)vec->a.x == (int)vec->b.x && (int)vec->a.y == (int)vec->b.y))
	{
		if (!limit || ((int)vec->a.x > limit->l && (int)vec->a.x < limit->r
		&& (int)vec->a.y > limit->t && (int)vec->a.y < limit->b))
			ft_setpixel(data->surface, (int)vec->a.x, (int)vec->a.y, color);
		e2 = tab[4];
		if (e2 > -tab[0] && (int)vec->a.x != (int)vec->b.x)
		{
			tab[4] -= tab[2];
			vec->a.x = (int)vec->a.x + tab[1];
		}
		if (e2 < tab[2] && (int)vec->a.y != (int)vec->b.y)
		{
			tab[4] += tab[0];
			vec->a.y = (int)vec->a.y + tab[3];
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

	vec1.a = (t_pos){rect.x, rect.y};
	vec1.b = (t_pos){rect.x + rect.w, rect.y};
	vec2.a = (t_pos){rect.x, rect.y};
	vec2.b = (t_pos){rect.x, rect.y + rect.h};
	vec3.a = (t_pos){rect.x + rect.w, rect.y};
	vec3.b = (t_pos){rect.x + rect.w, rect.y + rect.h};
	vec4.a = (t_pos){rect.x, rect.y + rect.h};
	vec4.b = (t_pos){rect.x + rect.w, rect.y + rect.h};
	draw_line(data, &vec1, color, 0);
	draw_line(data, &vec2, color, 0);
	draw_line(data, &vec3, color, 0);
	draw_line(data, &vec4, color, 0);
}
