/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:45:51 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 21:44:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_exit(t_data *data)
{
	SDL_DestroyRenderer(data->sdl.renderer);
	SDL_DestroyWindow(data->sdl.window);
	TTF_CloseFont(data->font);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	ft_set_cursor(t_data *data)
{
	t_pos	a;
	t_pos	b;

	a.x = WIN_W / 2 - 10;
	a.y = WIN_H / 2;
	b.x = WIN_W / 2 + 10;
	b.y = WIN_H / 2;
	draw_line(data, a, b, 0xFF5BE50B, 0);
	a.x = WIN_W / 2;
	a.y = WIN_H / 2 - 10;
	b.x = WIN_W / 2;
	b.y = WIN_H / 2 + 10;
	draw_line(data, a, b, 0xFF5BE50B, 0);
}

void	ft_game_loop(t_data *data)
{
	ft_rc_wolfcalc(data);
	ft_minimap(data);
	data->texture = SDL_CreateTextureFromSurface(
	data->sdl.renderer, data->surface);
	SDL_FreeSurface(data->surface);
	SDL_RenderCopy(data->sdl.renderer, data->texture, 0, 0);
	SDL_RenderPresent(data->sdl.renderer);
	while (1)
	{
		if (ft_get_events(data))
		{
			SDL_RenderClear(data->sdl.renderer);
			ft_rc_wolfcalc(data);
			ft_minimap(data);
			if (data->gamemode == 1)
				ft_set_cursor(data);
			data->texture = SDL_CreateTextureFromSurface(
			data->sdl.renderer, data->surface);
			SDL_FreeSurface(data->surface);
			SDL_RenderCopy(data->sdl.renderer, data->texture, 0, 0);
			SDL_RenderPresent(data->sdl.renderer);
		}
	}
}

int		main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
		ft_arg_invalid();
	ft_init_data(argv[1], &data);
	ft_game_loop(&data);
	return (0);
}
