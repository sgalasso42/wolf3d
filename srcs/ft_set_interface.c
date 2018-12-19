/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:46:59 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 20:54:48 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_config(t_data *data)
{
	SDL_Rect	rect;

	rect.x = 200;
	rect.y = 200;
	rect.h = 372;
	rect.w = 560;

	ft_draw_rect(rect,  0x10000000, 0, data);
	ft_draw_border(rect, 0xFFFFFFFF, data);
}

void	ft_set_interface(t_data *data)
{
	SDL_Rect	rect;

	rect.x = 15;
	rect.y = 15;
	rect.w = 138;
	rect.h = 20;

	ft_draw_rect(rect,  0x00000000, 0, data);
	ft_draw_border(rect, 0xFFFFFFFF, data);

	rect.x = 170;
	rect.w = 60;
	ft_draw_rect(rect, 0xFF000000, 0, data);
	ft_draw_border(rect, 0xFFFFFFFF, data);
	if (data->setting == 1)
	{
		ft_set_config(data);
		ft_set_menu_config(data);
	}
}
