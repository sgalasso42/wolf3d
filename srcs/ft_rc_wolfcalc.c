/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 18:52:22 by sgalasso         ###   ########.fr       */
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

void		ft_get_color(int axis, t_ray *ray)
{
	if (axis == 1) // y
	{
		if (ray->angle_d >= 0 && ray->angle_d <= 180)
			ray->color = 0xFF4D56D6;
		else
			ray->color = 0xFF51DB6A;
	}
	else if (axis == 2) // x
	{
		if (ray->angle_d >= 90 && ray->angle_d <= 270)
			ray->color = 0xFFDBAC51;
		else
			ray->color = 0xFFEFEFEF;
	}
}

void		ft_calc_distance(int i, int x, t_thread *thread)
{
	double	distance_x;
	double	distance_y;
	t_pos	player_pos;	// position calculee
	double	alpha_d;	// angle entre direction et ray en degres
	double	alpha_r;	// idem en radian
	double	angle_r;	// angle radian
	t_pos	pos;

	player_pos.x = thread->data->player.position.x * BLOC_SIZE;
	player_pos.y = thread->data->player.position.y * BLOC_SIZE;

	// anle en fonction de x
	thread->ray[i].angle_d =
	(thread->data->player.direction - 30) + (x * (60.0 / WIN_W));
	// passage en radian
	angle_r = thread->ray[i].angle_d * M_PI / 180;

	alpha_d = fabs(thread->data->player.direction - thread->ray[i].angle_d);
	alpha_r = alpha_d * M_PI / 180;

	pos.x = thread->data->player.position.x * BLOC_SIZE;
	pos.y = thread->data->player.position.y * BLOC_SIZE;;

	while (pos.x > 0 && pos.x < thread->data->map_sz.w * BLOC_SIZE
	&& pos.y > 0 && pos.y < thread->data->map_sz.h * BLOC_SIZE)
	{
		if (ft_is_inwall(&pos, thread->data)) // y
		{
			distance_x = pos.x - player_pos.x;
			distance_y = (int)pos.y - player_pos.y; //
			thread->ray[i].distance = ft_pythagore(distance_x, distance_y);
			thread->ray[i].dist_minimap = thread->ray[i].distance;
			// correction fisheye
			thread->ray[i].distance = thread->ray[i].distance * cos(alpha_r);
			// get color of wall
			ft_get_color(1, &(thread->ray[i]));
			return ;
		}

		pos.x += -cos(angle_r) * 1;

		if (ft_is_inwall(&pos, thread->data)) // x
		{
			distance_x = (int)pos.x - player_pos.x;
			distance_y = pos.y - player_pos.y;
			thread->ray[i].distance = ft_pythagore(distance_x, distance_y);
			thread->ray[i].dist_minimap = thread->ray[i].distance;
			// correction fisheye
			thread->ray[i].distance = thread->ray[i].distance * cos(alpha_r);
			// get color of wall
			ft_get_color(2, &(thread->ray[i]));
			return ;
		}
		pos.y += -sin(angle_r) * 1;
	}
	// out of map
	thread->ray[i].distance = -1;
}

void		ft_calc_ray(int i, int x, t_thread *thread)
{
	double	height;

	height = 0;
	ft_calc_distance(i, x, thread);
	//printf("dir : %f : dist : %f\n", data->player.direction, ray.distance);

	if (thread->ray[i].distance >= 0)
		height = (BLOC_SIZE / thread->ray[i].distance) * DIST_SCREEN;

	thread->ray[i].wall_top = (WIN_H - height) / 2;
	thread->ray[i].wall_bot = WIN_H - ((WIN_H - height) / 2);
}

void		*ft_calc_frame(void *arg)
{
	t_thread	*thread;
	double		x;
	double		y;
	int			i;

	i = 0;
	thread = (t_thread *)arg;
	x = thread->x_start;
	while (x < WIN_W)
	{
		y = 0;
		ft_calc_ray(i, x, thread);
		while (y < WIN_H)
		{
			if (y < thread->ray[i].wall_top)
				ft_setpixel(thread->data->surface, x, y, 0x0);
			else if (y >= thread->ray[i].wall_top && y <= thread->ray[i].wall_bot)
				ft_setpixel(thread->data->surface, x, y, thread->ray[i].color);
			else
				ft_setpixel(thread->data->surface, x, y, 0x0);
			y++;
		}
		x += 8;
		i++;
	}
	pthread_exit(0);
}
static SDL_Surface	*ft_new_surface(int height, int width)
{
	SDL_Surface *surface;
	Uint32 r, g, b, a;

	r = 0x000000ff;
	g = 0x0000ff00;
	b = 0x00ff0000;
	a = 0xff000000;

	if (!(surface = SDL_CreateRGBSurface(0, width, height, 32, r, g, b, a)))
	{
		SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
		exit(EXIT_FAILURE); // recup exit
	}
	return (surface);
}
void				ft_rc_wolfcalc(t_data *data)
{
	int i;

	i = 0;
	data->surface = ft_new_surface(WIN_H, WIN_W);
	while (i < 8)
	{	
		data->thread[i].x_start = i;
		data->thread[i].data = data;
		ft_bzero(data->thread[i].ray,
		sizeof(t_ray) * (WIN_W / 8));
		pthread_create(&(data->thread[i].th), NULL,
		ft_calc_frame, (void *)&(data->thread[i]));
		i++;
	}
	i = 0;
	while (i < 8)
	{
		pthread_join(data->thread[i].th, 0);
		pthread_join(data->thread[i].th, 0);
		i++;
	}
}
