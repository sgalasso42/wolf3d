/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/17 02:03:36 by sgalasso         ###   ########.fr       */
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
		return (1);
	return (0);
}

int			ft_calc_distance(int x, t_data *data)
{
	double	alpha_d; // angle entre direction et ray en degres
	double	alpha_r; // idem en radian
	double	angle_d; // degres
	double	angle_r; // radian
	double	distance;
	t_pos	pos;

	// anle en fonction de x
	angle_d = (data->player.direction - 30) + (x * (60.0 / WIN_W));
	// passage en radian
	angle_r = angle_d * M_PI / 180;
	
	alpha_d = fabs(data->player.direction - angle_d);
	alpha_r = alpha_d * M_PI / 180;

	pos.x = data->player.position.x * BLOC_SIZE;
	pos.y = data->player.position.y * BLOC_SIZE;;
	while (pos.x > 0 && pos.x < data->map_sz.w * BLOC_SIZE
	&& pos.y > 0 && pos.y < data->map_sz.h * BLOC_SIZE)
	{
		if (ft_is_inwall(&pos, data))
		{
			distance = ft_pythagore(
			pos.x - data->player.position.x * BLOC_SIZE,
			pos.y - data->player.position.y * BLOC_SIZE);

			// correction dish eye
			distance = distance * cos(alpha_r);
			return (distance);
		}

		pos.x += -cos(angle_r) * 1;
		pos.y += -sin(angle_r) * 1;

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
	printf("dir : %f : dist : %f\n", data->player.direction, distance);
	if (distance > 0)
	{
		height = (BLOC_SIZE / distance) * DIST_SCREEN;
		//printf("height : %f\n", height);
	}

	if (data->player.direction > 0 && data->player.direction < 90)
		ray.pole = 0;
	else if (data->player.direction > 90 && data->player.direction < 180)
		ray.pole = 1;
	else if (data->player.direction > 180 && data->player.direction < 270)
		ray.pole = 2;
	else
		ray.pole = 3;

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
				if (ray.pole == 3)
					SDL_SetRenderDrawColor(data->sdl.renderer, 105, 105, 105, 255);
				else if (ray.pole == 6)
					SDL_SetRenderDrawColor(data->sdl.renderer, 250, 100, 55, 255);
				else if (ray.pole == 4)
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
