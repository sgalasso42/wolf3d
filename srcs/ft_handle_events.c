/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:08:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 16:19:20 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
