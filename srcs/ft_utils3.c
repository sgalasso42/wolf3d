/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:42:49 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:16:17 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_remove_light(Uint8 *component, double delta)
{
	if (*component > 0)
		*component = (*component * (1 - delta));
}

static int		ft_apply_shade(Uint32 c, double delta)
{
	SDL_Color color;

	delta > 0.9 ? delta = 0.9 : 0;
	delta /= 1.50;
	c |= 0xFF000000;
	color = (SDL_Color){c >> 24, c >> 16, c >> 8, c};
	ft_remove_light(&color.r, delta);
	ft_remove_light(&color.g, delta);
	ft_remove_light(&color.b, delta);
	ft_remove_light(&color.a, delta);
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
}

Uint32			ft_light_shade(double distance, Uint32 color)
{
	double	delta;

	delta = distance / 300;
	return (ft_apply_shade(color, delta));
}

void			ft_setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
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

Uint32			ft_getpixel(SDL_Surface *surface, int x, int y)
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
