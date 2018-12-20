/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 02:47:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_movement_normal(t_data *data)
{
	double		angle_r;
	t_pos		pos;

	if (data->gamemode == 1)
		return (0);

	// passage en radian
	angle_r = data->player.direction * M_PI / 180;

	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_UP)
	{ // ^
		pos.x = data->player.position.x * BLOC_SIZE + -cos(angle_r) * 10;
		pos.y = data->player.position.y * BLOC_SIZE;
		if (!ft_is_inwall(&pos, data))
			data->player.position.x += -cos(angle_r) * 0.2;
		pos.y = data->player.position.y * BLOC_SIZE + -sin(angle_r) * 10;
		if (!ft_is_inwall(&pos, data))
			data->player.position.y += -sin(angle_r) * 0.2;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_DOWN)
	{ // v
		pos.x = data->player.position.x * BLOC_SIZE - -cos(angle_r) * 10;
		pos.y = data->player.position.y * BLOC_SIZE;
		if (!ft_is_inwall(&pos, data))
			data->player.position.x -= -cos(angle_r) * 0.2;
		pos.y = data->player.position.y * BLOC_SIZE - -sin(angle_r) * 10;
		if (!ft_is_inwall(&pos, data))
			data->player.position.y -= -sin(angle_r) * 0.2;
		return (1);
	}
	return (0);
}

static int		ft_movement_gaming(t_data *data)
{
	double		angle_r;
	t_pos		pos;

	if (data->gamemode == 0)
		return (0);

	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_W)
	{ // w
		angle_r = data->player.direction * M_PI / 180;
		pos.x = data->player.position.x * BLOC_SIZE + -cos(angle_r) * 10;
		pos.y = data->player.position.y * BLOC_SIZE;
		if (!ft_is_inwall(&pos, data))
			data->player.position.x += -cos(angle_r) * 0.2;
		pos.y = data->player.position.y * BLOC_SIZE + -sin(angle_r) * 10;
		if (!ft_is_inwall(&pos, data))
			data->player.position.y += -sin(angle_r) * 0.2;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_S)
	{ // s
		// passage en radian
		angle_r = data->player.direction * M_PI / 180;
		pos.x = data->player.position.x * BLOC_SIZE - -cos(angle_r) * 10;
		pos.y = data->player.position.y * BLOC_SIZE;
		if (!ft_is_inwall(&pos, data))
			data->player.position.x -= -cos(angle_r) * 0.2;
		pos.y = data->player.position.y * BLOC_SIZE - -sin(angle_r) * 10;
		if (!ft_is_inwall(&pos, data))
			data->player.position.y -= -sin(angle_r) * 0.2;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_A)
	{ // a
		// passage en radian
		angle_r = (data->player.direction + 90) * M_PI / 180;
		pos.x = data->player.position.x * BLOC_SIZE - -cos(angle_r) * 10;
		pos.y = data->player.position.y * BLOC_SIZE;
		if (!ft_is_inwall(&pos, data))
			data->player.position.x -= -cos(angle_r) * 0.2;
		pos.y = data->player.position.y * BLOC_SIZE - -sin(angle_r) * 10;
		if (!ft_is_inwall(&pos, data))
			data->player.position.y -= -sin(angle_r) * 0.2;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_D)
	{ // d
		// passage en radian
		angle_r = (data->player.direction - 90) * M_PI / 180;
		pos.x = data->player.position.x * BLOC_SIZE - -cos(angle_r) * 10;
		pos.y = data->player.position.y * BLOC_SIZE;
		if (!ft_is_inwall(&pos, data))
			data->player.position.x -= -cos(angle_r) * 0.2;
		pos.y = data->player.position.y * BLOC_SIZE - -sin(angle_r) * 10;
		if (!ft_is_inwall(&pos, data))
			data->player.position.y -= -sin(angle_r) * 0.2;
		return (1);
	}
	return (0);
}

static int		ft_rotation_normal(t_data *data)
{
	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
	{ // >
		data->player.direction = (int)(data->player.direction + 5) % 360;
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_LEFT)
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

static int		ft_keyboard(t_data *data)
{
	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		ft_exit(data);
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_I)
		data->setting = (data->setting) ? 0 : 1;
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
	else if (ft_movement_normal(data) || ft_rotation_normal(data))
		return (1);
	else if (ft_movement_gaming(data))
		return (1);
	else
		return (0);
	return (1);
}

static int		ft_mouse_motion(t_data *data)
{
	if (data->mouse.x > 0)
	{ // mouse left
		data->player.direction = (int)(data->player.direction
		+ abs(data->mouse.x) / 4) % 360;
	}
	else if (data->mouse.x < 0)
	{ // mouse_right
		if (data->player.direction - 5 > 0)
			data->player.direction = (int)(data->player.direction
			- abs(data->mouse.x) / 4);
		else
			data->player.direction = 360;
	}
	else
		return (0);
	return (1);
}

int				ft_get_events(t_data *data)
{
	if (SDL_PollEvent(&(data->sdl.event)) == 1)
	{
		SDL_GetRelativeMouseState(&(data->mouse.x), &(data->mouse.y));
		if (data->sdl.event.type == SDL_QUIT)
			ft_exit(data);
		else if (data->sdl.event.type == SDL_KEYDOWN && ft_keyboard(data))
			return (1);
		if (data->gamemode == 1
		&& data->sdl.event.type == SDL_MOUSEMOTION && ft_mouse_motion(data))
			return (1);
	}
	return (0);
}
