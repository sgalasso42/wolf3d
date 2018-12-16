/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:46:24 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/16 11:35:20 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

# define WIN_H 500
# define WIN_W 800

# define BLOC_SIZE 10

# define DIST_SCREEN 277

typedef struct s_pos	t_pos;
typedef struct s_size	t_size;
typedef struct s_coef	t_coef;
typedef struct s_ray	t_ray;
typedef struct s_sdl	t_sdl;
typedef struct s_player	t_player;
typedef struct s_data	t_data;

struct					s_pos
{
	double				x;
	double				y;
};

struct					s_size
{
	int					h;
	int					w;
};

struct					s_coef
{
	int					x;
	int					y;
};

struct					s_ray
{
	int					wall_top;
	int					wall_bot;
	int					wall_color;
	int					pole; // Nord Est Sud Ouest
};

struct					s_sdl
{
	SDL_Event			event;
	SDL_Window      	*window;
	SDL_Renderer    	*renderer;
};

struct					s_player
{
	t_pos				position;
	double				direction;
	int					cam_height;
	int					visual_field;
};

struct					s_data
{
	t_sdl				sdl;
	TTF_Font			*font;
	int					**map;	// map
	t_size				map_sz;	// map size
	t_player			player;	// position camera

	int					current_color;
};

void					ft_exit(t_data *data);

void					ft_init_data(char *map, t_data *data);
void					ft_get_map(char *map, t_data *data);

int						ft_get_events(t_data *data);
void					ft_rc_wolfcalc(t_data *data);

#endif
