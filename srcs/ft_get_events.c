/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 17:36:32 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_keyboard1(const Uint8 *state, t_data *data)
{
	if (state[SDL_SCANCODE_I] && data->setting == 1)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		data->setting = 0;
	}
	else if (state[SDL_SCANCODE_I] && data->setting == 0)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		data->setting = 1;
	}
	else if (state[SDL_SCANCODE_KP_8])
		data->player.speed -= (data->player.speed > 0.04) ? 0.02 : 0;
	else if (state[SDL_SCANCODE_KP_9])
		data->player.speed += (data->player.speed < 0.3) ? 0.02 : 0;
	else if (state[SDL_SCANCODE_KP_MULTIPLY])
		data->player.sensibility -= (data->player.sensibility > 1) ? 1 : 0;
	else if (state[SDL_SCANCODE_KP_DIVIDE])
		data->player.sensibility += (data->player.sensibility < 10) ? 1 : 0;
	else
		return (0);
	return (1);
}

static int		ft_keyboard2(const Uint8 *state, t_data *data)
{
	if (state[SDL_SCANCODE_1])
		data->gamemode = 0;
	else if (state[SDL_SCANCODE_2])
		data->gamemode = 1;
	else if (state[SDL_SCANCODE_3])
		data->dev_mode = (data->dev_mode) ? 0 : 1;
	else if (state[SDL_SCANCODE_T])
		data->texturing = (data->texturing) ? 0 : 1;
	else if (state[SDL_SCANCODE_L])
		data->lightshade = (data->lightshade) ? 0 : 1;
	else if (state[SDL_SCANCODE_KP_PLUS]
	&& data->minimap.mnp_size * ZOOM_P < 50)
		data->minimap.mnp_size *= ZOOM_P;
	else if (state[SDL_SCANCODE_KP_MINUS]
	&& data->minimap.mnp_size * ZOOM_L > 10)
		data->minimap.mnp_size *= ZOOM_L;
	else
		return (0);
	return (1);
}

static int		ft_mouse_motion(t_data *data)
{
	if (data->mouse.x > 0.0)
	{
		data->player.direction = (int)(data->player.direction
		+ abs(data->mouse.x) / data->player.sensibility) % 360;
		return (1);
	}
	else if (data->mouse.x < 0.0)
	{
		data->player.direction = (int)(data->player.direction
		- abs(data->mouse.x) / data->player.sensibility) % 360;
		if (data->player.direction < 0)
			data->player.direction = 360 + data->player.direction;
		return (1);
	}
	return (0);
}

static int		ft_move_events(const Uint8 *state, t_data *data)
{
	int		ok;

	ok = 0;
	if (data->gamemode == 0 && data->setting == 0)
	{
		if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
			ok = (ft_movement_normal(state, data)) ? 1 : ok;
		if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
			ok = (ft_rotation_normal(state, data)) ? 1 : ok;
	}
	else if (data->setting == 0)
	{
		if (data->mouse.x || data->mouse.y)
			ok = (ft_mouse_motion(data)) ? 1 : ok;
		if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_S])
			ok = (ft_movement_gaming(state, data)) ? 1 : ok;
		if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
			ok = (ft_lateral_gaming(state, data)) ? 1 : ok;
	}
	return (ok);
}

int				ft_get_events(t_data *data)
{
	const Uint8 *state;
	int			ok;

	ok = 0;
	SDL_PollEvent(&(data->sdl.event));
	state = SDL_GetKeyboardState(0);
	SDL_GetRelativeMouseState(&(data->mouse.x), &(data->mouse.y));
	if (state[SDL_SCANCODE_ESCAPE])
		ft_exit(data);
	if (data->sdl.event.type == SDL_QUIT)
		ft_exit(data);
	if (data->sdl.event.type == SDL_KEYDOWN)
		ok = (ft_keyboard1(state, data) || ft_keyboard2(state, data)) ? 1 : ok;
	ok = (ok) ? 1 : ft_move_events(state, data);
	return (ok);
}
