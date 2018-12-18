/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:45:51 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 14:26:42 by sgalasso         ###   ########.fr       */
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
	ft_rc_wolfcalc(data);
	ft_minimap(data);
	SDL_RenderPresent(data->sdl.renderer);
	while (1)
	{
		if (ft_get_events(data))
		{
			SDL_RenderClear(data->sdl.renderer);
			ft_rc_wolfcalc(data);
			ft_minimap(data);
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
