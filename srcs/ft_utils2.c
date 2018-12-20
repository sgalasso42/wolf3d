/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:39:40 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:16:41 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double              ft_pythagore(int a, int b)
{
	return (sqrt(a * a + b * b));
}

SDL_Color		ft_set_color(t_data *data, int i)
{
	if ((data->gamemode == 0 && i == 0)
	|| (data->gamemode == 1 && i == 1)
	|| (data->dev_mode == 1 && i == 2))
		return (ft_hex_to_rgb(H_RED));
	return (ft_hex_to_rgb(H_GREEN));
}

void			ft_set_cursor(t_data *data)
{
	t_vec	vec;

	vec.a = (t_pos){WIN_W / 2 - 10, WIN_H / 2};
	vec.b = (t_pos){WIN_W / 2 + 10, WIN_H / 2};
	draw_line(data, &vec, 0xFF5BE50B, 0);
	vec.a = (t_pos){WIN_W / 2, WIN_H / 2 - 10};
	vec.b = (t_pos){WIN_W / 2, WIN_H / 2 + 10};
	draw_line(data, &vec, 0xFF5BE50B, 0);
}

void			ft_set_string(SDL_Rect rect, char *text,
				SDL_Color color, t_data *data)
{
	SDL_Surface			*surface;
	SDL_Texture			*texture;

	surface = TTF_RenderText_Blended(data->font, text, color);
	rect.w = (rect.h * surface->w) / surface->h;
	texture = SDL_CreateTextureFromSurface(data->sdl.renderer, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(data->sdl.renderer, texture, NULL, &(rect)) < 0)
		ft_failure_exit("wolf3d: string error", data);
}

SDL_Color		ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}
