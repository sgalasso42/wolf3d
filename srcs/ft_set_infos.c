/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:45 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 01:15:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Color	ft_set_color(t_data *data, int i)
{
	if ((data->gamemode == 0 && i == 0)
	|| (data->gamemode == 1 && i == 1)
	|| (data->dev_mode == 1  && i == 2))
		return (ft_hex_to_rgb(H_RED));
	return (ft_hex_to_rgb(H_GREEN));
}

void	ft_set_menu_config(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){230,300,500,30};
	ft_set_string(rect, "Speed", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){230,350,500,30};
	ft_set_string(rect, "[ * ] [ / ]   Sensibility", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){230,400,500,30};
	ft_set_string(rect, "[ l ]         Light shading", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){230,450,500,30};
	ft_set_string(rect, "[ + ] [ - ]  Minimap zoom", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){230,500,500,30};
	ft_set_string(rect, "[ Esc ]     Exit", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){230,230,500,50};
	ft_set_string(rect, "SETTINGS", ft_hex_to_rgb(H_GREEN), data);
}

void	ft_dev_mode(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){20,18,150,15};
	ft_set_string(rect, "1 normal", ft_set_color(data, 0), data);
}

void	ft_set_infos(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){20,18,150,15};
	ft_set_string(rect, "1 normal", ft_set_color(data, 0), data);
	rect = (SDL_Rect){87,18,150,15};
	ft_set_string(rect, "2 gamimg", ft_set_color(data, 1), data);
	rect = (SDL_Rect){WIN_W / 2 - 75,660,150,20};
	ft_set_string(rect, "SETTINGS : [ i ]", ft_set_color(data, 3), data);
	rect = (SDL_Rect){184,18,150,15};
	ft_set_string(rect, "3 dev", ft_set_color(data, 2), data);
	if (data->dev_mode == 1)
		ft_dev_mode(data);
	if (data->setting == 1)
		ft_set_menu_config(data);
}
