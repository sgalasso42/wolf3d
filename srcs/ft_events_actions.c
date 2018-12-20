/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 23:09:52 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:12:14 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_movement_normal(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = data->player.direction * M_PI / 180;
	if (state[SDL_SCANCODE_UP])
		ft_movement_plus(angle_r, data);
	else if (state[SDL_SCANCODE_DOWN])
		ft_movement_minus(angle_r, data);
	return (1);
}

int				ft_rotation_normal(const Uint8 *state, t_data *data)
{
	if (state[SDL_SCANCODE_RIGHT])
		data->player.direction = (int)(data->player.direction + 5) % 360;
	else if (state[SDL_SCANCODE_LEFT])
	{
		if (data->player.direction - 5 > 0)
			data->player.direction = (int)(data->player.direction - 5);
		else
			data->player.direction = 360;
	}
	return (1);
}

int				ft_movement_gaming(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = data->player.direction * M_PI / 180;
	if (state[SDL_SCANCODE_W])
		ft_movement_plus(angle_r, data);
	else if (state[SDL_SCANCODE_S])
		ft_movement_minus(angle_r, data);
	return (1);
}

int				ft_lateral_gaming(const Uint8 *state, t_data *data)
{
	double		angle_r;

	angle_r = (data->player.direction + 90) * M_PI / 180;
	if (state[SDL_SCANCODE_D])
		ft_movement_plus(angle_r, data);
	else if (state[SDL_SCANCODE_A])
		ft_movement_minus(angle_r, data);
	return (1);
}

int				ft_mouse_motion(t_data *data)
{
	if (data->mouse.x > 0)
		data->player.direction = (int)(data->player.direction
		+ abs(data->mouse.x) / data->player.sensibility) % 360;
	else if (data->mouse.x < 0)
	{
		if (data->player.direction - 5 > 0)
			data->player.direction = (int)(data->player.direction
			- abs(data->mouse.x) / data->player.sensibility);
		else
			data->player.direction = 360;
	}
	return (1);
}
