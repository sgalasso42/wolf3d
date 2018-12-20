/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 23:06:35 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:12:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_movement_plus(double angle_r, t_data *data)
{
	t_pos		pos_h;
	t_pos		pos_v;

	pos_h.x = (data->player.position.x * BLOC_SIZE)
	- cos(angle_r) * (data->player.speed * 150);
	pos_h.y = (data->player.position.y * BLOC_SIZE);
	pos_v.x = (data->player.position.x * BLOC_SIZE);
	pos_v.y = (data->player.position.y * BLOC_SIZE)
	- sin(angle_r) * (data->player.speed * 150);
	if (!ft_is_inwall(&pos_v, data))
		data->player.position.y += -sin(angle_r) * data->player.speed;
	if (!ft_is_inwall(&pos_h, data))
		data->player.position.x += -cos(angle_r) * data->player.speed;
}

void			ft_movement_minus(double angle_r, t_data *data)
{
	t_pos		pos_h;
	t_pos		pos_v;

	pos_h.x = (data->player.position.x * BLOC_SIZE)
	+ cos(angle_r) * (data->player.speed * 150);
	pos_h.y = (data->player.position.y * BLOC_SIZE);
	pos_v.x = (data->player.position.x * BLOC_SIZE);
	pos_v.y = (data->player.position.y * BLOC_SIZE)
	+ sin(angle_r) * (data->player.speed * 150);
	if (!ft_is_inwall(&pos_v, data))
		data->player.position.y += sin(angle_r) * data->player.speed;
	if (!ft_is_inwall(&pos_h, data))
		data->player.position.x += cos(angle_r) * data->player.speed;
}

int				ft_keyboard1(t_data *data)
{
	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		ft_exit(data);
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_I)
		data->setting = (data->setting) ? 0 : 1;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_8)
		data->player.speed -= (data->player.speed > 0.04) ? 0.02 : 0;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_9)
		data->player.speed += (data->player.speed < 0.3) ? 0.02 : 0;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_MULTIPLY)
		data->player.sensibility -= (data->player.sensibility > 1) ? 1 : 0;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_DIVIDE)
		data->player.sensibility += (data->player.sensibility < 10) ? 1 : 0;
	else
		return (0);
	return (1);
}

int				ft_keyboard2(t_data *data)
{
	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_1)
		data->gamemode = 0;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_2)
		data->gamemode = 1;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_3)
		data->dev_mode = (data->dev_mode) ? 0 : 1;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_L)
		data->lightshade = (data->lightshade) ? 0 : 1;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS
	&& data->minimap.mnp_size * ZOOM_P < 50)
		data->minimap.mnp_size *= ZOOM_P;
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS
	&& data->minimap.mnp_size * ZOOM_L > 10)
		data->minimap.mnp_size *= ZOOM_L;
	else
		return (0);
	return (1);
}
