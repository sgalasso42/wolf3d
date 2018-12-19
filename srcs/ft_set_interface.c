/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:46:59 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 16:50:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_interface(t_data *data)
{
	SDL_Rect	rect;

	rect.x = 10;
	rect.y = 10;
	rect.w = 150;
	rect.h = 50;

	//ft_draw_rect(SDL_Rect rect, Uint32 color,
	//0, t_data *data);

	ft_draw_border(rect, 0xFFFFFFFF, data);
}
