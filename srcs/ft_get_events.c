/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/12 10:22:17 by sgalasso         ###   ########.fr       */
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
}

static int		ft_mouse_motion(t_data *data)
{
	if (ft_mouseenter(data))
		return (1);
	else if (ft_mouseleave(data))
		return (1);
	if (data->drag == 1)
	{
		ft_grid_event(data);
		return (1);
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

static int		ft_keyboard(t_data *data)
{
	if (data->sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{ // esc
		ft_exit(data);
	}
	return (0);
}

int		ft_get_events(t_data *data)
{
	if (SDL_PollEvent(&(data->sdl.event)) == 1)
	{
		if (data->sdl.event.type == SDL_QUIT)
			ft_exit(data);
		else if (data->sdl.event.type == SDL_KEYDOWN
		&& ft_keyboard(data))
			return (1);
		/*SDL_GetMouseState(&(data->mouse.x), &(data->mouse.y));
		if (data->sdl.event.type == SDL_MOUSEMOTION
		&& ft_mouse_motion(data))
			return (1);
		else if (data->sdl.event.type == SDL_MOUSEBUTTONDOWN
		&& ft_mouse_button_down(data))
			return (1);
		else if (data->sdl.event.type == SDL_MOUSEBUTTONUP
		&& ft_mouse_button_up(data))
			return (1);*/
	}
	return (0);
}
