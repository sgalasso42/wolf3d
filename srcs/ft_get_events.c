/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 14:17:26 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_is_inmap(t_pos *pos, t_data *data)
{
	return (pos->x > 0 && pos->x < data->map_sz.w * BLOC_SIZE
	&& pos->y > 0 && pos->y < data->map_sz.h * BLOC_SIZE);
}

int				ft_movement(double angle_r, int dir, t_data *data)
{
	double		move_x;
	double		move_y;
	t_pos		pos_h;
	t_pos		pos_v;

	move_y = sin(angle_r) * data->player.speed;
	move_x = cos(angle_r) * data->player.speed;
	if (dir == 1)
	{
		pos_h.x = (data->player.position.x * BLOC_SIZE) - move_x * 150;
		pos_h.y = (data->player.position.y * BLOC_SIZE);
		pos_v.x = (data->player.position.x * BLOC_SIZE);
		pos_v.y = (data->player.position.y * BLOC_SIZE) - move_y * 150;
		move_y = -move_y;
		move_x = -move_x;
	}
	else
	{
		pos_h.x = (data->player.position.x * BLOC_SIZE) + move_x * 150;
		pos_h.y = (data->player.position.y * BLOC_SIZE);
		pos_v.x = (data->player.position.x * BLOC_SIZE);
		pos_v.y = (data->player.position.y * BLOC_SIZE) + move_y * 150;
	}
	if (ft_is_inmap(&pos_v, data) && !(ft_is_inwall(&pos_v, data)))
		data->player.position.y += move_y;
	if (ft_is_inmap(&pos_h, data) && !(ft_is_inwall(&pos_h, data)))
		data->player.position.x += move_x;
	return (1);
}

int				ft_movement_normal(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = data->player.direction * M_PI / 180;
	if (state[SDL_SCANCODE_UP])
		return (ft_movement(angle_r, 1, data));
	else if (state[SDL_SCANCODE_DOWN])
		return (ft_movement(angle_r, 0, data));
	return (0);
}

int				ft_rotation_normal(const Uint8 *state, t_data *data)
{
	if (state[SDL_SCANCODE_RIGHT])
	{
		data->player.direction = (int)(data->player.direction + 5) % 360;
		return (1);
	}
	else if (state[SDL_SCANCODE_LEFT])
	{
		if (data->player.direction - 5 > 0)
			data->player.direction = (int)(data->player.direction - 5);
		else
			data->player.direction = 360;
		return (1);
	}
	return (0);
}

int				ft_movement_gaming(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = data->player.direction * M_PI / 180;
	if (state[SDL_SCANCODE_W])
		return (ft_movement(angle_r, 1, data));
	else if (state[SDL_SCANCODE_S])
		return (ft_movement(angle_r, 0, data));
	return (0);
}

int				ft_lateral_gaming(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = (data->player.direction + 90) * M_PI / 180;
	if (state[SDL_SCANCODE_D])
		return (ft_movement(angle_r, 1, data));
	else if (state[SDL_SCANCODE_A])
		return (ft_movement(angle_r, 0, data));
	return (0);
}

int				ft_keyboard(const Uint8 *state, t_data *data)
{
	if (state[SDL_SCANCODE_I])
	{
		if (data->setting == 1)
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			data->setting = 0;
		}
		else
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			data->setting = 1;
		}
	}
	else if (state[SDL_SCANCODE_KP_8])
		data->player.speed -= (data->player.speed > 0.04) ? 0.02 : 0;
	else if (state[SDL_SCANCODE_KP_9])
		data->player.speed += (data->player.speed < 0.3) ? 0.02 : 0;
	else if (state[SDL_SCANCODE_KP_MULTIPLY])
		data->player.sensibility -= (data->player.sensibility > 1) ? 1 : 0;
	else if (state[SDL_SCANCODE_KP_DIVIDE])
		data->player.sensibility += (data->player.sensibility < 10) ? 1 : 0;
	else if (state[SDL_SCANCODE_1])
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

int				ft_mouse_motion(t_data *data)
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
		ok = (ft_keyboard(state, data)) ? 1 : ok;
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
