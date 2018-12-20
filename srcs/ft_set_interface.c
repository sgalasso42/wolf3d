/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:46:59 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 20:38:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_config(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){200,200,560,372};
	ft_draw_rect(rect,  0x10000000, 0, data);
	ft_draw_border(rect, 0xFFFFFFFF, data);
}

void	ft_bloc_devmode(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){15,48,200,35};
	ft_draw_rect(rect, 0x10000000, 0, data);
	rect = (SDL_Rect){15,98,200,35};
	ft_draw_rect(rect, 0x10000000, 0, data);
	rect = (SDL_Rect){15,138,200,35};
	ft_draw_rect(rect, 0x10000000, 0, data);
	rect = (SDL_Rect){15,178,200,35};
	ft_draw_rect(rect, 0x10000000, 0, data);
}

void	ft_set_interface(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){15,15,138,20};
	ft_draw_rect(rect,  0x00000000, 0, data);
	ft_draw_border(rect, 0xFFFFFFFF, data);
	rect = (SDL_Rect){170,15,60,20};
	ft_draw_rect(rect, 0xFF000000, 0, data);
	ft_draw_border(rect, 0xFFFFFFFF, data);
	if (data->setting == 1)
		ft_set_config(data);
	if (data->dev_mode == 1)
		ft_bloc_devmode(data);
}
