/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:45:51 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/12 11:20:18 by sgalasso         ###   ########.fr       */
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

void	ft_game_loop(t_data *data)
{
	//ft_rc_wolfcalc(data);
	SDL_RenderPresent(data->sdl.renderer);
	while (1)
	{
		if (ft_get_events(data))
		{
			SDL_RenderClear(data->sdl.renderer);
			//ft_rc_wolfcalc(data);
			SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
			SDL_RenderPresent(data->sdl.renderer);
		}
	}
}

int		main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
	{
		ft_putendl(
		"Usage : ./wolf3d [map_name]");
		return (0);
	}
	ft_init_data(argv[1], &data);
	ft_game_loop(&data);
	return (0);
}
