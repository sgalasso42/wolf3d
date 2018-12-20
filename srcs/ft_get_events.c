/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 15:47:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_movement(double angle_r, int dir, t_data *data)
{
	t_pos		pos_h;
	t_pos		pos_v;

	if (dir == 1)
	{ // ^
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
	else
	{ // v
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
}

static int		ft_movement_normal(const Uint8 *state, t_data *data)
{
	double		angle_r;

	// passage en radian
	angle_r = data->player.direction * M_PI / 180;

	if (state[SDL_SCANCODE_UP])
	{ // ^
		ft_movement(angle_r, 1, data);
	}
	else if (state[SDL_SCANCODE_DOWN])
	{ // v
		ft_movement(angle_r, 0, data);
	}
	else
		return (0);
	return (1);
}

static int		ft_rotation_normal(const Uint8 *state, t_data *data)
{
	if (state[SDL_SCANCODE_RIGHT])
	{ // >
		data->player.direction = (int)(data->player.direction + 5) % 360;
	}
	else if (state[SDL_SCANCODE_LEFT])
	{ // <
		if (data->player.direction - 5 > 0)
			data->player.direction = (int)(data->player.direction - 5);
		else
			data->player.direction = 360;
	}
	else
		return (0);
	return (1);
}

static int		ft_movement_gaming(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = data->player.direction * M_PI / 180;

	if (state[SDL_SCANCODE_W])
	{ // w
		ft_movement(angle_r, 1, data);
	}
	else if (state[SDL_SCANCODE_S])
	{ // s
		ft_movement(angle_r, 0, data);
	}
	else
		return (0);
	return (1);
}

static int		ft_lateral_gaming(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = (data->player.direction + 90) * M_PI / 180;

	if (state[SDL_SCANCODE_D])
	{ // a
		ft_movement(angle_r, 1, data);
	}
	else if (state[SDL_SCANCODE_A])
	{ // d
		ft_movement(angle_r, 0, data);
	}
	else
		return (0);
	return (1);
}

static int		ft_keyboard(t_data *data)
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
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_1)
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

static int		ft_mouse_motion(t_data *data)
{
	if (data->mouse.x > 0)
	{ // mouse left
		data->player.direction = (int)(data->player.direction
		+ abs(data->mouse.x) / data->player.sensibility) % 360;
	}
	else if (data->mouse.x < 0)
	{ // mouse_right
		if (data->player.direction - 5 > 0)
			data->player.direction = (int)(data->player.direction
			- abs(data->mouse.x) / data->player.sensibility);
		else
			data->player.direction = 360;
	}
	else
		return (0);
	return (1);
}

int				ft_get_events(t_data *data)
{
	const Uint8 *state;
	int			ok;
	
	ok = 0;
	state = SDL_GetKeyboardState(0);
	if (data->gamemode == 0)
	{
		if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
		{
			ft_movement_normal(state, data);
			ok = 1;
		}
		if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
		{
			ft_rotation_normal(state, data);
			ok = 1;
		}
	}
	else
	{
		if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_S])
		{
			ft_movement_gaming(state, data);
			ok = 1;
		}
		if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
		{
			ft_lateral_gaming(state, data);
			ok = 1;
		}	
	}
	if (SDL_PollEvent(&(data->sdl.event)) == 1)
	{
		if (data->sdl.event.type == SDL_QUIT)
		{
			SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP | SDL_MOUSEMOTION);
			ft_exit(data);
		}
		else if (data->sdl.event.type == SDL_KEYDOWN && ft_keyboard(data))
			ok = 1;
		if (data->gamemode == 1)
		{
			SDL_GetRelativeMouseState(&(data->mouse.x), &(data->mouse.y));
			if (data->mouse.x || data->mouse.y)
			{
				ft_mouse_motion(data);
				ok = 1;
			}
		}
	}
	if (ok == 1)
		return (1);
	return (0);
}
