/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:45 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 21:14:00 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Color	ft_set_color(t_data *data, int i)
{
	SDL_Color	green;
	SDL_Color	red;

	green.r = 0;
	green.g = 255;
	green.b = 0;
	green.a = 255;

	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;

	// 0 normal

	if ((data->gamemode == 0 && i == 0) 
			|| (data->gamemode == 1 && i == 1)
			|| (data->dev_mode == 1  && i == 2))
		return (red);
	return (green);
}

void	ft_set_infos(t_data *data)
{
	SDL_Rect	rect;

	rect.y = 18;
	rect.w = 150;
	rect.h = 15;

	rect.x = 20;
	ft_set_string(rect, "1 normal", ft_set_color(data, 0), data);
	rect.x = 87;
	ft_set_string(rect, "2 gamimg", ft_set_color(data, 1), data);
	rect.x = 460;
	rect.y = 660;
	rect.h = 20;
	ft_set_string(rect, "SETTINGS : i", ft_set_color(data, 3), data);
	ft_dev_mode(data);
}

void	ft_dev_mode(t_data *data)
{
	SDL_Rect	rect;
	
	rect.y = 18;
	rect.w = 150;
	rect.h = 15;
	rect.x = 184;

	ft_set_string(rect, "3 dev", ft_set_color(data, 2), data);
}

void	ft_set_menu_config(t_data *data)
{
	SDL_Rect	rect;
	SDL_Color	green;

	green.r = 0;
	green.g = 255;
	green.b = 0;
	green.a = 255;

	rect.x = 230;
	rect.w = 500;
	rect.h = 40;

	rect.y = 280;
	ft_set_string(rect, "Speed", green, data);
	rect.y = 320;
	ft_set_string(rect, "Sensibility", green, data);
	rect.y = 370;
	ft_set_string(rect, "Light shading [L]", green, data);
	rect.y = 420;
	ft_set_string(rect, "Minimap zoom [+][-]", green, data);
	rect.y = 470;
	ft_set_string(rect, "Quit [esc]", green, data);
	rect.y = 230;
	rect.x = 380;
	ft_set_string(rect, "SETTINGS", green, data);
}
