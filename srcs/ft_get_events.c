/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 10:32:41 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*int				ft_mouseenter(t_data *data)
{
	int i;

	i = 0;
	if (!data->mouse_in)
	{
		while (i < NB_OF_BTN_EDITOR)
		{
			if (SDL_PointInRect(&(data->mouse),
			&(data->editor.button[i].btn_rect)))
			{
				data->mouse_in = &(data->editor.button[i]);
				data->mouse_in->btn_state = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int				ft_mouseleave(t_data *data)
{
	if (data->mouse_in)
	{
		if (!SDL_PointInRect(&(data->mouse),
		&(data->mouse_in->btn_rect)))
		{
			data->mouse_in->btn_state = 0;
			data->mouse_in = 0;
			return (1);
		}
	}
	return (0);
}*/

/*static int		ft_mouse_button_down(t_data *data)
{
	if (data->sdl.event.button.button == SDL_BUTTON_LEFT)
	{
		if (data->mouse_in == &(data->editor.button[TAB_SAVE]))
		{
			ft_export_map(data);
			return (1);
		}
		else if (data->mouse_in == &(data->editor.button[TAB_EDT_EXIT]))
		{
			data->exit_msg = "Are you sure you want to exit ? [y][n]";
			return (1);
		}
		else if (data->mouse_in == &(data->editor.button[TAB_EDT_NEW]))
			ft_menu_loop(data);
		else if (data->mouse_in == &(data->editor.button[TAB_EDT_OPEN]))
		{
			data->menu.aff_maps = 1;
			ft_menu_loop(data);
		}
		else if (data->mouse.x >= 400 && data->mouse.x <= 1400 // to update
		&& data->mouse.y >= 150 && data->mouse.y <= 850)
		{
			data->drag = 1;
			if (ft_grid_event(data))
				return (1);
		}
		else if (data->mouse_in == &(data->editor.button[TAB_3DPREV]))
		{
			data->editor.preview_3d = 1;
			return (1);
		}
	}
	return (0);
}*/

/*static int		ft_mouse_button_up(t_data *data)
{
	if (data->drag == 1)
	{
		data->drag = 0;
		return (1);
	}
	return (0);
}*/

static int		ft_movement_normal(t_data *data)
{
	double		angle_r;
	t_pos		pos;

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

	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_W)
	{ // w
		// passage en radian
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
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_LEFT)
	{ // <
		data->player.direction = (int)(data->player.direction - 5) % 360;
		return (1);
	}
	return (0);
}

static int		ft_keyboard(t_data *data)
{
	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{ // esc
		ft_exit(data);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_1)
	{ // 1
		data->gamemode = 0;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_2)
	{ // 2
		data->gamemode = 1;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS
	&& data->minimap.mnp_size * ZOOM_P < 50)
	{ // minimap +
		data->minimap.mnp_size *= ZOOM_P;
		return (1);
	}
	else if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS
	&& data->minimap.mnp_size * ZOOM_L > 10)
	{ // minimap -
		data->minimap.mnp_size *= ZOOM_L;
		return (1);
	}
	else if (data->gamemode == 0)
	{
		if (ft_movement_normal(data) || ft_rotation_normal(data))
			return (1);
	}
	else if (data->gamemode == 1)
	{
		if (ft_movement_gaming(data))
			return (1);
	}
	return (0);
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
		data->player.direction = (int)(data->player.direction
		- abs(data->mouse.x) / 4) % 360;
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
		/*else if (data->sdl.event.type == SDL_MOUSEBUTTONDOWN
		&& ft_mouse_button_down(data))
			return (1);
		else if (data->sdl.event.type == SDL_MOUSEBUTTONUP
		&& ft_mouse_button_up(data))
			return (1);*/
	}
	return (0);
}
