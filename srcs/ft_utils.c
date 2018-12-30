/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:56:50 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/30 13:28:03 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		ft_pythagore(int a, int b)
{
	return (sqrt(a * a + b * b));
}

void		ft_set_cursor(t_data *data)
{
	t_pos	a;
	t_pos	b;

	a = (t_pos){WIN_W / 2 - 10,WIN_H / 2};
	b = (t_pos){WIN_W / 2 + 10,WIN_H / 2};
	draw_line(data, a, b, 0xFF5BE50B, 0);
	a = (t_pos){WIN_W / 2,WIN_H / 2 - 10};
	b = (t_pos){WIN_W / 2,WIN_H / 2 + 10};
	draw_line(data, a, b, 0xFF5BE50B, 0);
}

static void		ft_remove_light(Uint8 *component, double delta, int arg)
{
	if (*component > 0)
		*component = (*component * (1 - delta) + ((0x0 >> arg) * delta));
}

static int		ft_apply_shade(Uint32 c, double delta)
{
	SDL_Color color;

	delta > 0.9 ? delta = 0.9 : 0;
	delta /= 1.50;
	c |= 0xFF000000;
	color = (SDL_Color){c >> 24, c >> 16, c >> 8, c};
	ft_remove_light(&color.r, delta, 24);
	ft_remove_light(&color.g, delta, 16);
	ft_remove_light(&color.b, delta, 8);
	ft_remove_light(&color.a, delta, 0);
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
}

Uint32		ft_light_shade(double distance, Uint32 color)
{
	double  delta;

	delta = distance / 300;
	return (ft_apply_shade(color, delta));
}
