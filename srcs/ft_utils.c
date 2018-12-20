/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:56:50 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 01:15:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_set_string(SDL_Rect rect, char *text, SDL_Color color, t_data *data)
{
	SDL_Surface			*surface;
	SDL_Texture			*texture;

	surface	= TTF_RenderText_Blended(data->font, text, color);
	rect.w = (rect.h * surface->w) / surface->h; // largeur relative
	texture = SDL_CreateTextureFromSurface(data->sdl.renderer, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(data->sdl.renderer, texture, NULL, &(rect)) < 0)
		exit(EXIT_FAILURE); // exit proprement todo
}

SDL_Color	ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

static void		ft_remove_light(Uint8 *component, double delta, int arg)
{
	if (*component > 0)
		*component = (*component * (1 - delta) + ((0x0 >> arg) * delta));
}

static int		ft_apply_shade(Uint32 c, double delta)
{
	SDL_Color color;

	delta > 0.9 ? delta = 0.9 : 0;
	delta /= 1.50;
	c |= 0xFF000000;
	color.r = c >> 24;
	color.g = c >> 16;
	color.b = c >> 8;
	color.a = c;
	ft_remove_light(&color.r, delta, 24);
	ft_remove_light(&color.g, delta, 16);
	ft_remove_light(&color.b, delta, 8);
	ft_remove_light(&color.a, delta, 0);
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
}

Uint32		ft_light_shade(double distance, Uint32 color)
{
	double  delta;

	delta = distance / 300;
	return (ft_apply_shade(color, delta));
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

void		ft_draw_rect(SDL_Rect rect, Uint32 color, t_limit *limit, t_data *data)
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

void		ft_draw_border(SDL_Rect rect, Uint32 color, t_data *data)
{
	t_pos p1;
	t_pos p2;
	t_pos p3;
	t_pos p4;

	p1.x = rect.x;
	p1.y = rect.y;

	p2.x = rect.x + rect.w;
	p2.y = rect.y;

	p3.x = rect.x;
	p3.y = rect.y + rect.h;

	p4.x = rect.x + rect.w;
	p4.y = rect.y + rect.h;

	draw_line(data, p1, p2, color, 0);
	draw_line(data, p1, p3, color, 0);
	draw_line(data, p2, p4, color, 0);
	draw_line(data, p3, p4, color, 0);
}
