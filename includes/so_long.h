/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:33:22 by hateisse          #+#    #+#             */
/*   Updated: 2023/03/26 19:46:46 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define GAME_TITLE "so_long"
# define GREEN 2263842

# define ESCAPE 65307
# define W 119
# define D 100
# define S 115
# define A 97

# define GROUND_SPRITE "./sprites/tile00.xpm"
# define WALL_SPRITE "./sprites/tile01.xpm"
# define COLLECTIBLE_SPRITE "./sprites/ball.xpm"
# define EXIT_SPRITE "./sprites/ladder.xpm"
# define PLAYER_S0_SPRITE "./sprites/player_S00.xpm"

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_map		*map_info;
	struct s_img_ptr	*img_ptrs;
}						t_window;

typedef struct s_img_ptr
{
	void				*img_ptr;
	int					y;
	int					x;
	int					type;
	struct s_img_ptr	*next;
	struct s_img_ptr	*prev;
}						t_img_ptr;

typedef struct s_map
{
	char				**map;
	int					y_len;
	int					x_len;
	int					players;
	int					p_pos[2];
	int					collectibles;
	int					can_be_collected;
	int					exit_reachable;
	int					game_end;
	int					exits;
	int					moves;
}						t_map;

void					ft_create_hooks(t_window *win_info);
int						handle_key_pressed(int key, t_window *win_info);
int						all_collected(char **map);

char					*ft_type_to_path(int type, t_window *win_info);

void					ft_load_n_display_image(t_window *win_info, int y,
							int x, int type);
void					ft_display_images(t_window *win_info);

int						get_new_pos(int vector, int move_direction, int *p_pos);
void					edit_p_pos_and_map(int *npos, int *p_pos, char **map,
							int newobj);

void					destroy_all_images(t_img_ptr **lst, void *mlx_ptr);

int						target_is_object(char **map, int *p_pos, int object,
							int move_direction);
void					move_to_exit(t_window *win_info);
void					move_to_ground(char **map, int *p_pos, int move,
							t_window *win_info);
void					move_to_collectible(char **map, int *p_pos, int move,
							t_window *w_info);
void					update_and_print_moves(t_window *win_info);

void					ft_lsaddback(t_img_ptr **lst, t_img_ptr *new);
void					ft_lsremoveif(t_window *win_info, int type, int y,
							int x);
t_img_ptr				*ft_lsnew(int type, int y, int x, void *img_ptr);
t_img_ptr				*ft_lslast(t_img_ptr *lst);
void					*ft_lschr_img(t_img_ptr *img_ptrs, int y, int x,
							int type);

int						ft_on_window_close(t_window *win_info);
int						ft_close_window(t_window *win_info);

t_window				*ft_init_and_create_window(t_map *map_info);

void					ft_trim_nl(char *line);

void					ft_free_map_info(t_map *map_info);
void					ft_free_win_info(t_window *win_info);

void					ft_error(int errno, t_map *map_info);
void					ft_error_2(int errno, t_map *map_info);
void					ft_error_map_info(int errno, t_map *map_info);
void					ft_error_mlx(int errno, t_map *map_info);

t_map					*ft_init_map_info(void);

void					ft_get_map_file(char *filename, t_map *map_info);
void					ft_parse_line(char *line, int y, int fst_or_lst,
							t_map *map_info);

void					ft_check_map_info_arguments(t_map *map_info);
void					ft_check_if_valid_path_exist(t_map *map_info);
void					ft_check_map_size(t_window *win_info);

void					ft_parse_map(t_map *map_info);

void					ft_set_ground_chars_to_zero(char **map);
void					ft_flood_fill(int y, int x, t_map *map_info);
void					check_exit_else_continue(char c, int y, int x,
							t_map *map_info);
#endif