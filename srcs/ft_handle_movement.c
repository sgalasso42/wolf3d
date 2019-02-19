/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:16:17 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 17:40:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_is_inmap(t_pos *pos, t_data *data)
{
	return (pos->x > 0 && pos->x < data->map_sz.w * BLOC_SIZE
	&& pos->y > 0 && pos->y < data->map_sz.h * BLOC_SIZE);
}

int				ft_movement(double angle_r, int dir, t_data *data)
{
	t_pos		move;
	t_pos		pos_h;
	t_pos		pos_v;

	move.y = sin(angle_r) * data->player.speed;
	move.x = cos(angle_r) * data->player.speed;
	pos_h.y = (data->player.position.y * BLOC_SIZE);
	pos_v.x = (data->player.position.x * BLOC_SIZE);
	if (dir == 1)
	{
		pos_h.x = (data->player.position.x * BLOC_SIZE) - move.x * 150;
		pos_v.y = (data->player.position.y * BLOC_SIZE) - move.y * 150;
		move.y = -move.y;
		move.x = -move.x;
	}
	else
	{
		pos_h.x = (data->player.position.x * BLOC_SIZE) + move.x * 150;
		pos_v.y = (data->player.position.y * BLOC_SIZE) + move.y * 150;
	}
	if (ft_is_inmap(&pos_v, data) && !(ft_is_inwall(&pos_v, data)))
		data->player.position.y += move.y;
	if (ft_is_inmap(&pos_h, data) && !(ft_is_inwall(&pos_h, data)))
		data->player.position.x += move.x;
	return (1);
}
