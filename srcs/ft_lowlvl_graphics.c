/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowlvl_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 13:34:51 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 20:59:12 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*ft_new_surface(int height, int width, t_data *data)
{
	SDL_Surface		*surface;
	Uint32			color[4];

	color[0] = 0x000000ff;
	color[1] = 0x0000ff00;
	color[2] = 0x00ff0000;
	color[3] = 0xff000000;
	if (!(surface = lt_push(SDL_CreateRGBSurface(
	0, width, height, 32, color[0], color[1], color[2], color[3]), ft_srfdel)))
		ft_err_exit("wolf3d: error: SDL_CreateRGBSurface() failed", data);
	return (surface);
}

void			ft_set_string(SDL_Rect rect, char *text,
				SDL_Color color, t_data *data)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*surface;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	if (!(surface = TTF_RenderText_Blended(data->font, text, color)))
		ft_err_exit("Wolf3d: Error while making surface", data);
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	if ((SDL_BlitScaled(surface, 0, data->surface, &sdl_rect)) == -1)
		ft_err_exit("Wolf3d: Error can't blit surface", data);
	SDL_FreeSurface(surface);
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

Uint32			ft_getpixel(SDL_Surface *surface, int x, int y, t_data *data)
{
	int				bpp;
	Uint8			*p;
	Uint32			ret;

	if ((SDL_LockSurface(surface)) != 0)
		ft_err_exit("wolf3d: error: SDL_LockSurface() failure", data);
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
