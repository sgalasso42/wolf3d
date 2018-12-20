/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_wolfcalc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:55:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 16:10:31 by sgalasso         ###   ########.fr       */
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
	if (data->map[y2][x2] == 1 || data->map[y2][x2] == 3)
		return (1);
	return (0);
}

Uint32		ft_get_color(int axis, int angle_d, int x, int y, t_data *data)
{
	Uint32		color;

	color = 0;
	if (axis == 1)
	{
		if ((angle_d >= 0 && angle_d <= 180) || angle_d >= 360)
			color = ft_getpixel(data->object[0].img_srf, x, y);
		else
			color = ft_getpixel(data->object[1].img_srf, x, y);
	}
	else if (axis == 2)
	{
		if (angle_d >= 90 && angle_d <= 270)
			color = ft_getpixel(data->object[2].img_srf, x, y);
		else
			color = ft_getpixel(data->object[3].img_srf, x, y);
	}
	return (color | 0xFF000000);
}

void		ft_get_raydata(int axis, t_pos pos,
			t_pos player_pos, double alpha_r, int i, t_thread *thread)
{
	double	distance_x;
	double	distance_y;

	if (axis == 1) // y
	{
		distance_x = pos.x - player_pos.x;
		distance_y = (int)pos.y - player_pos.y;
	}
	else // x
	{
		distance_x = (int)pos.x - player_pos.x;
		distance_y = pos.y - player_pos.y;
	}
	thread->ray[i].distance = ft_pythagore(distance_x, distance_y);
	thread->ray[i].dist_minimap = thread->ray[i].distance;
	thread->ray[i].distance = thread->ray[i].distance * cos(alpha_r);
	thread->ray[i].x = pos.x;
	thread->ray[i].y = pos.y;
	thread->ray[i].axis = axis;
}

void		ft_calc_distance(int i, int x, t_thread *thread)
{
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
			ft_get_raydata(1, pos, player_pos, alpha_r, i, thread);
			return ;
		}
		pos.x += -cos(angle_r) * 1;
		if (ft_is_inwall(&pos, thread->data)) // x
		{
			ft_get_raydata(2, pos, player_pos, alpha_r, i, thread);
			return ;
		}
		pos.y += -sin(angle_r) * 1;
	}
	// out of map
	thread->ray[i].distance = -1;
}

void					ft_calc_col(int i, int x, t_thread *thread)
{
	double	height;

	height = 0;
	ft_calc_distance(i, x, thread);
	if (thread->ray[i].distance >= 0)
		height = (BLOC_SIZE / thread->ray[i].distance) * DIST_SCREEN;
	thread->ray[i].wall_top = (WIN_H - height) / 2;
	thread->ray[i].wall_bot = WIN_H - ((WIN_H - height) / 2);
}

void					*ft_calc_frame(void *arg)
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
		ft_calc_col(i, x, thread);
		while (y < WIN_H)
		{
			if (y < thread->ray[i].wall_top)
				ft_setpixel(thread->data->surface, x, y, 0xFFFFFED6);
			else if (y >= thread->ray[i].wall_top && y <= thread->ray[i].wall_bot)
			{

				// ----------------------------------------------

				Uint32	color;
				double	y_pixel;
				double	h_textr;
				double	h_wall;
				int		y_textr;
				int		x_textr;

				y_pixel = (y - thread->ray[i].wall_top);
				h_textr = thread->data->object[0].img_srf->h;
				h_wall = thread->ray[i].wall_bot - thread->ray[i].wall_top;

				y_textr = h_textr * y_pixel / h_wall;

				/*x_textr = ft_abs(thread->data->object[0].img_srf->w
				- thread->ray[i].x);
				x_textr %= thread->data->object[0].img_srf->w;*/
				
				if (thread->ray[i].axis == 1)
				{
					x_textr = (thread->ray[i].x) % (BLOC_SIZE);
					x_textr *= 5.5;
				}
				else
				{
					x_textr = (thread->ray[i].y) % (BLOC_SIZE);
					x_textr *= 5.5;
				}

				color = ft_get_color(thread->ray[i].axis,
				thread->ray[i].angle_d, x_textr, y_textr, thread->data);
				
				// ----------------------------------------------		

				// light shading
				if (thread->data->lightshade == 1)
					color = ft_light_shade(thread->ray[i].distance, color);

				ft_setpixel(thread->data->surface, x, y, color);
			}
			else
				ft_setpixel(thread->data->surface, x, y, 0x0);
			y++;
		}
		x += 8;
		i++;
	}
	pthread_exit(0);
}

static SDL_Surface		*ft_new_surface(int height, int width)
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
