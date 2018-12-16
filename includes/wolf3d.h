/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:46:24 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/16 13:15:07 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

/*
 * ** Color text
 * */

# define C_NONE         "\033[0m"
# define C_BOLD         "\033[1m"
# define C_BLACK        "\033[30m"
# define C_RED          "\033[31m"
# define C_GREEN        "\033[32m"
# define C_BROWN        "\033[33m"
# define C_BLUE         "\033[34m"
# define C_MAGENTA      "\033[35m"
# define C_CYAN         "\033[36m"
# define C_GRAY         "\033[37m"



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
void	ft_err_malloc(void);
void	ft_err_malloc_free(char *line, int fd);
void	ft_arg_invalid(void);
void	ft_map_invalid(void);
void	ft_map_invalid_free(char *line, int fd);
int		ft_isspace(int c);
void	ft_check_valid_map(char *line, int fd);

#endif
