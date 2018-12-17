/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:00:12 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/17 01:36:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_draw_rect(int x, int y, int w, int h, int r, int g, int b, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			SDL_SetRenderDrawColor(data->sdl.renderer, r, g, b, 255);
			SDL_RenderDrawPoint(data->sdl.renderer, x + j, y + i);
			j++;
		}
		i++;
	}
}

void	ft_minimap(t_data *data)
{
	int		size = 20;
	int		i;
	int		j;

	// background
	ft_draw_rect(0, 0, size * data->map_sz.w,
	size * data->map_sz.h, 255, 255, 255, data);

	// walls
	i = 0;
	while (i < data->map_sz.h)
	{
		j = 0;
		while (j < data->map_sz.w)
		{
			if (data->map[i][j] > 0 && data->map[i][j] != 2)
				ft_draw_rect(j * size, i * size, size, size, 0, 0, 255, data);
			j++;
		}
		i++;
	}

	// direction
	double	rayon = 30;
	double	angle;
	double	step_x;
	double	step_y;

	// angle en radian
	angle = (data->player.direction - 30) * M_PI / 180;
	step_x = -cos(angle) * rayon;
	step_y = -sin(angle) * rayon;

	SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);

	SDL_RenderDrawLine(data->sdl.renderer,
	data->player.position.x * size, data->player.position.y * size,
	step_x + data->player.position.x * size, step_y + data->player.position.y * size);

	angle = (data->player.direction + 30) * M_PI / 180;
	step_x = -cos(angle) * rayon;
	step_y = -sin(angle) * rayon;

	SDL_RenderDrawLine(data->sdl.renderer,
	data->player.position.x * size, data->player.position.y * size,
	step_x + data->player.position.x * size, step_y + data->player.position.y * size);

	SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
}
