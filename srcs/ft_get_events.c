/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:03:00 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:10:31 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_get_multikey(int ok, const Uint8 *state, t_data *data)
{
	state = SDL_GetKeyboardState(0);
	if (data->gamemode == 0
	&& (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]))
		ok = ft_movement_normal(state, data);
	if (data->gamemode == 0
	&& (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT]))
		ok = ft_rotation_normal(state, data);
	if (data->gamemode != 0
	&& (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_S]))
		ok = ft_movement_gaming(state, data);
	if (data->gamemode != 0
	&& (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D]))
		ok = ft_lateral_gaming(state, data);
	return (ok);
}

int				ft_get_events(t_data *data)
{
	const Uint8		*state;
	int				ok;

	ok = 0;
	if (SDL_PollEvent(&(data->sdl.event)) == 1)
	{
		if (data->sdl.event.type == SDL_QUIT)
			ft_exit(data);
		else if (data->sdl.event.type == SDL_KEYDOWN)
			ok = (ft_keyboard1(data) || ft_keyboard2(data));
		SDL_GetRelativeMouseState(&(data->mouse.x), &(data->mouse.y));
		if (data->gamemode == 1 && (data->mouse.x || data->mouse.y))
			ok = ft_mouse_motion(data);
		ok = ft_get_multikey(ok, state, data);
	}
	return (ok);
}
