/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/17 15:09:30 by sgalasso         ###   ########.fr       */
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
	if (data->map[y2][x2] == 1)
		return (1);
	return (0);
}

void		ft_get_color(int axis, t_ray *ray, t_data *data)
{
	(void)data;
	if (axis == 1) // y
	{
		if (ray->angle_d >= 0 && ray->angle_d <= 180)
			ray->color_index = 0;
		else
			ray->color_index = 1;
	}
	else if (axis == 2) // x
	{
		if (ray->angle_d >= 90 && ray->angle_d <= 270)
			ray->color_index = 2;
		else
			ray->color_index = 3;
	}
}

t_ray		ft_calc_distance(int x, t_data *data)
{
	double	alpha_d; // angle entre direction et ray en degres
	double	alpha_r; // idem en radian
	double	angle_r; // angle radian
	t_ray	ray;
	t_pos	pos;

	// anle en fonction de x
	ray.angle_d = (data->player.direction - 30) + (x * (60.0 / WIN_W));
	// passage en radian
	angle_r = ray.angle_d * M_PI / 180;
	
	alpha_d = fabs(data->player.direction - ray.angle_d);
	alpha_r = alpha_d * M_PI / 180;

	pos.x = data->player.position.x * BLOC_SIZE;
	pos.y = data->player.position.y * BLOC_SIZE;;

	while (pos.x > 0 && pos.x < data->map_sz.w * BLOC_SIZE
	&& pos.y > 0 && pos.y < data->map_sz.h * BLOC_SIZE)
	{
		if (ft_is_inwall(&pos, data))
		{
			ray.distance = ft_pythagore(
			pos.x - data->player.position.x * BLOC_SIZE,
			pos.y - data->player.position.y * BLOC_SIZE);

			// correction dish eye
			ray.distance = ray.distance * cos(alpha_r);

			// get color of wall
			ft_get_color(1, &ray, data);
			return (ray);
		}

		pos.x += -cos(angle_r) * 1;

		if (ft_is_inwall(&pos, data))
		{
			ray.distance = ft_pythagore(
			pos.x - data->player.position.x * BLOC_SIZE,
			pos.y - data->player.position.y * BLOC_SIZE);

			// correction dish eye
			ray.distance = ray.distance * cos(alpha_r);

			// get color of wall
			ft_get_color(2, &ray, data);
			return (ray);
		}

		pos.y += -sin(angle_r) * 1;

	}
	// out of map
	ray.distance = -1;
	return (ray);
}

t_ray		ft_calc_ray(int x, t_data *data)
{
	double	height;
	t_ray	ray;

	height = 0;
	ray = ft_calc_distance(x, data);
	//printf("dir : %f : dist : %f\n", data->player.direction, ray.distance);

	if (ray.distance >= 0)
	{
		height = (BLOC_SIZE / ray.distance) * DIST_SCREEN;
		//printf("height : %f\n", height);
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
				if (ray.color_index == 0)
					SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 255, 255);
				else if (ray.color_index == 1)
					SDL_SetRenderDrawColor(data->sdl.renderer, 0, 255, 0, 255);
				else if (ray.color_index == 2)
					SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);
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
