/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:56:50 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 11:17:08 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Color	ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	hexa |= 0xFF000000;
	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

void		ft_setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int			bpp;
	Uint8		*p;

	if (x < 0 || x > WIN_W || y < 0 || y > WIN_H)
		return ;
	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	(bpp == 1) ? *p = pixel : 0;
	(bpp == 2) ? *(Uint16 *)p = pixel : 0;
	(bpp == 4) ? *(Uint32 *)p = pixel : 0;
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
	}
}

Uint32		ft_getpixel(SDL_Surface *surface, int x, int y)
{
	int				bpp;
	Uint8			*p;
	Uint32			ret;

	SDL_LockSurface(surface);
	x = ft_abs(--x);
	y = ft_abs(--y);
	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		ret = *p;
	else if (bpp == 2)
		ret = *(Uint16 *)p;
	else if (bpp == 3)
	{
		ret = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
		(p[0] << 16 | p[1] << 8 | p[2]) : (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		ret = *(Uint32 *)p;
	else
		ret = 0;
	SDL_UnlockSurface(surface);
	return (ret);
}

static void		bresenham_tab(int *tab, t_pos p1, t_pos p2)
{
	tab[0]	 = abs((int)p2.x - (int)p1.x);
	tab[1] = (int)p1.x < (int)p2.x ? 1 : -1;
	tab[2] = abs((int)p2.y - (int)p1.y);
	tab[3] = (int)p1.y < (int)p2.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) / 2;
}

void		draw_line(t_data *data, t_pos p1, t_pos p2, Uint32 color, t_limit *limit)
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

void		ft_draw_rect(int x, int y, int w, int h, Uint32 color,
t_limit *limit, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (!limit || (x + j > limit->l && x + j < limit->r
						&& y + i > limit->t && y + i < limit->b))
				ft_setpixel(data->surface, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void		ft_draw_border(t_data *data, int x, int y)
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

	draw_line(data, p1, p2, 0xFFFFFFFF, 0);
	draw_line(data, p1, p3, 0xFFFFFFFF, 0);
	draw_line(data, p2, p4, 0xFFFFFFFF, 0);
	draw_line(data, p3, p4, 0xFFFFFFFF, 0);
}
