/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/16 00:36:03 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		ft_pythagore(int a, int b)
{
	return (sqrt(a * a + b * b));
}

int			ft_is_inwall(t_pos *pos, t_data *data)
{
	int		x2;
	int		y2;

	x2 = pos->x / BLOC_SIZE;
	y2 = pos->y / BLOC_SIZE;
	if (data->map[y2][x2] > 0 && data->map[y2][x2] != 2)
	{
		data->current_color = data->map[y2][x2];
		return (1);
	}
	return (0);
}

int			ft_calc_distance(int x, t_data *data)
{
	double	angle;
	double	distance;
	t_pos	pos;

	distance = 0;
	angle = data->player.direction + (x * (60.0 / WIN_W));
	printf("angle : %f\n", angle);
	pos.x = data->player.position.x * BLOC_SIZE;
	pos.y = data->player.position.y * BLOC_SIZE;
	while (pos.x > 0 && pos.x < data->map_sz.w * BLOC_SIZE
	&& pos.y > 0 && pos.y < data->map_sz.h * BLOC_SIZE)
	{
		if (ft_is_inwall(&pos, data))
		{
			distance = ft_pythagore(pos.x - data->player.position.x,
			pos.y - data->player.position.y);
			printf("distance : %f\n", distance);
			return (distance);
		}
		//printf("angle : %f\n", angle);
		//printf("pos.x : %f\n", pos.x);
		//printf("pos.y : %f\n", pos.y);
		pos.x += 1.0 * cos(angle); // 1.0 a changer pour opti
		pos.y += 1.0 * sin(angle); // 1.0 a changer pour opti
	}
	return (-1);
}

t_ray		ft_calc_ray(int x, t_data *data)
{
	double	distance;
	double	height;
	t_ray	ray;

	height = 0;
	distance = ft_calc_distance(x, data);
	if (distance > 0)
	{
		//printf("%d : distance : %f\n", x, distance);
		height = (BLOC_SIZE / distance) * 277; // 277 trouve sur internet
		//printf("height : %f\n", height);
		//printf("hauteur mur : %f\n", height);
	}

	ray.wall_top = (WIN_H - height) / 2;
	ray.wall_bot = WIN_H - ((WIN_H - height) / 2);
	
	return (ray);
}

void		ft_rc_wolfcalc(t_data *data)
{
	t_ray	ray;
	double	y;
	double	x;

	x = 0;
	//printf("direction : %f\n", data->player.direction);
	while (x < WIN_W)
	{
		y = 0;
		ray = ft_calc_ray(x, data);
		while (y < WIN_H)
		{
			if (y < ray.wall_top)
			{
				SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
				SDL_RenderDrawPoint(data->sdl.renderer, x, y);
			}
			else if (y >= ray.wall_top && y <= ray.wall_bot)
			{
				if (data->current_color == 3)
					SDL_SetRenderDrawColor(data->sdl.renderer, 105, 105, 105, 255);
				else if (data->current_color == 6)
					SDL_SetRenderDrawColor(data->sdl.renderer, 250, 100, 55, 255);
				else if (data->current_color == 4)
					SDL_SetRenderDrawColor(data->sdl.renderer, 70, 44, 5, 255);
				else
					SDL_SetRenderDrawColor(data->sdl.renderer, 255, 255, 255, 255);
				SDL_RenderDrawPoint(data->sdl.renderer, x, y);
			}
			else
			{
				SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
				SDL_RenderDrawPoint(data->sdl.renderer, x, y);
			}
			y++;
		}
		ft_bzero(&ray, sizeof(t_ray));
		x++;
	}
}
