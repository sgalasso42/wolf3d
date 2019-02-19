/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:46:24 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/19 17:24:23 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <pthread.h>
# include <time.h>

# define H_GREEN 0x00FF00FF
# define H_RED 0xFF0000FF

# define WIN_H 700
# define WIN_W 1000
# define BLOC_SIZE 50
# define DIST_SCREEN 900

# define ZOOM_P 1.1
# define ZOOM_L 0.9

typedef struct s_limit		t_limit;
typedef struct s_pos		t_pos;
typedef struct s_vec		t_vec;
typedef struct s_size		t_size;
typedef struct s_coef		t_coef;
typedef struct s_ray		t_ray;
typedef struct s_thread		t_thread;
typedef struct s_object		t_object;
typedef struct s_sdl		t_sdl;
typedef struct s_player		t_player;
typedef struct s_minimap	t_minimap;
typedef struct s_data		t_data;

struct						s_limit
{
	int					t;
	int					b;
	int					l;
	int					r;
};

struct						s_pos
{
	double				x;
	double				y;
};

struct						s_vec
{
	t_pos				p1;
	t_pos				p2;
};

struct						s_size
{
	int					h;
	int					w;
};

struct						s_coef
{
	int					x;
	int					y;
};

struct						s_sdl
{
	SDL_Event			event;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
};

struct						s_ray
{
	int					x;
	int					y;
	int					axis;
	double				angle_d;
	double				distance;
	double				dist_minimap;
	double				wall_top;
	double				wall_bot;
};

struct						s_thread
{
	pthread_t			th;
	t_data				*data;
	int					x_start;
	t_ray				ray[WIN_W / 8];
};

struct						s_object
{
	SDL_Surface			*img_srf;
};

struct						s_player
{
	t_pos				position;
	double				direction;
	int					cam_height;
	int					visual_field;
	int					sensibility;
	double				speed;
};

struct						s_minimap
{
	double				mnp_size;
	t_pos				origin;
	t_limit				limit;
	t_size				map_size;
	t_pos				pos_play;
	t_pos				centre;
	t_pos				diff;
};

struct						s_data
{
	t_sdl				sdl;
	int					endinitsdl;
	TTF_Font			*font;
	int					**map;
	t_object			object[4];
	t_size				map_sz;
	t_player			player;
	t_thread			thread[8];
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	t_minimap			minimap;
	int					texturing;
	int					lightshade;
	int					gamemode;
	int					setting;
	int					dev_mode;
	t_coef				mouse;
	Uint32				time_last;
	int					nb_frame;
	int					fps;
};

void						ft_exit(t_data *data);
void						ft_err_exit(char *msg, t_data *data);

void						ft_get_map(char *map, t_data *data);
void						ft_init_data(char *map, t_data *data);

int							ft_movement(double angle_r, int dir, t_data *data);
int							ft_movement_gaming(const Uint8 *state,
							t_data *data);
int							ft_lateral_gaming(const Uint8 *state,
							t_data *data);
int							ft_movement_normal(const Uint8 *state,
							t_data *data);
int							ft_rotation_normal(const Uint8 *state,
							t_data *data);
int							ft_get_events(t_data *data);

int							ft_is_inwall(t_pos *pos, t_data *data);
Uint32						ft_get_color(int axis, int angle_d,
							t_coef pos, t_data *data);
Uint32						ft_get_color2(int axis, int angle_d);
void						ft_assign_color(int x, int y,
							int i, t_thread *thread);
void						ft_calc_distance(int i, int x, t_thread *thread);
void						ft_rc_wolfcalc(t_data *data);

void						ft_set_infos(t_data *data);
void						ft_set_interface(t_data *data);
void						ft_minimap(t_data *data);

double						ft_pythagore(int a, int b);
void						ft_set_cursor(t_data *data);
Uint32						ft_light_shade(double distance, Uint32 color);
void						ft_srfdel(void **ap);
SDL_Color					ft_hex_to_rgb(int hexa);
void						draw_line(t_data *data, t_vec vec,
							Uint32 color, t_limit *limit);
void						ft_draw_rect(SDL_Rect rect, Uint32 color,
							t_limit *limit, t_data *data);
void						ft_draw_border(SDL_Rect rect, Uint32 color,
							t_data *data);
SDL_Surface					*ft_new_surface(int height,
							int width, t_data *data);
void						ft_set_string(SDL_Rect rect, char *text,
							SDL_Color color, t_data *data);
void						ft_setpixel(SDL_Surface *surface,
							int x, int y, Uint32 pixel);
Uint32						ft_getpixel(SDL_Surface *surface,
							int x, int y, t_data *data);

#endif
