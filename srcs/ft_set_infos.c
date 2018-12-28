/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:45 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/28 16:40:51 by sgalasso         ###   ########.fr       */
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
	char		*speed_str;
	char		*sens_str;
	char		*light_str;
	char		*txtr_str;
	char		*zoom_str;

	if (!(speed_str = ft_itoa((int)(data->player.speed * 100))))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(sens_str = ft_itoa(data->player.sensibility)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(light_str = ft_itoa(data->lightshade)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(txtr_str = ft_itoa(data->texturing)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(zoom_str = ft_itoa(data->minimap.mnp_size)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);

	rect = (SDL_Rect){230,240,500,35};
	ft_set_string(rect, "SETTINGS", ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){230,300,500,25};
	ft_set_string(rect, "[ 8 9 ]  Speed", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){500,300,500,25};
	ft_set_string(rect, speed_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){230,340,500,25};
	ft_set_string(rect, "[ * / ]  Sensibility", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){500,340,500,25};
	ft_set_string(rect, sens_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){230,380,500,25};
	ft_set_string(rect, "[ l ]  Light shading", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){500,380,500,25};
	ft_set_string(rect, light_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){230,420,500,25};
	ft_set_string(rect, "[ t ]  Texturing", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){500,420,500,25};
	ft_set_string(rect, txtr_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){230,460,500,25};
	ft_set_string(rect, "[ + - ]  Minimap zoom", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){500,460,500,25};
	ft_set_string(rect, zoom_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){230,500,500,25};
	ft_set_string(rect, "[ Esc ]  Exit", ft_hex_to_rgb(H_GREEN), data);

	lt_release(speed_str);
	lt_release(sens_str);
	lt_release(light_str);
	lt_release(txtr_str);
	lt_release(zoom_str);
}

void	ft_dev_mode(t_data *data)
{
	SDL_Rect	rect;
	char		*fps_str;
	char		*frame_str;
	char		*posx_str;
	char		*posy_str;
	char		*dir_str;

	if (!(fps_str = ft_itoa(data->fps)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(frame_str = ft_itoa(data->nb_frame)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(posx_str = ft_itoa(data->player.position.x * BLOC_SIZE)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(posy_str = ft_itoa(data->player.position.y * BLOC_SIZE)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);
	if (!(dir_str = ft_itoa(data->player.direction)))
		ft_err_exit("wolf3d: error: itoa, out of memory", data);

	rect = (SDL_Rect){20,18,150,15};
	ft_set_string(rect, "1 normal", ft_set_color(data, 0), data);
	rect = (SDL_Rect){20,50,150,30};
	ft_set_string(rect, "fps : ", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){80,50,150,30};
	ft_set_string(rect, fps_str, ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){160,50,150,30};
	ft_set_string(rect, frame_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){20,100,150,30};
	ft_set_string(rect, "position.x : ", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){160,100,150,30};
	ft_set_string(rect, posx_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){20,140,150,30};
	ft_set_string(rect, "position.y : ", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){160,140,150,30};
	ft_set_string(rect, posy_str, ft_hex_to_rgb(H_GREEN), data);

	rect = (SDL_Rect){20,180,150,30};
	ft_set_string(rect, "direction : ", ft_hex_to_rgb(H_GREEN), data);
	rect = (SDL_Rect){160,180,150,30};
	ft_set_string(rect, dir_str, ft_hex_to_rgb(H_GREEN), data);
	
	lt_release(fps_str);
	lt_release(frame_str);
	lt_release(posx_str);
	lt_release(posy_str);
	lt_release(dir_str);
}

void	ft_set_infos(t_data *data)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){20,18,150,15};
	ft_set_string(rect, "1 normal", ft_set_color(data, 0), data);
	rect = (SDL_Rect){87,18,150,15};
	ft_set_string(rect, "2 gaming", ft_set_color(data, 1), data);
	rect = (SDL_Rect){WIN_W / 2 - 75,660,150,20};
	ft_set_string(rect, "SETTINGS : [ i ]", ft_set_color(data, 3), data);
	rect = (SDL_Rect){184,18,150,15};
	ft_set_string(rect, "3 dev", ft_set_color(data, 2), data);
	if (data->setting == 1)
		ft_set_menu_config(data);
	else if (data->dev_mode == 1)
		ft_dev_mode(data);
}
