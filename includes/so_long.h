/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:58:42 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 15:09:51 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <string.h>

# define TILE_SIZE 64
# define WIN_TITLE "so_long"

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}	t_player;

typedef struct s_counts
{
	int	players;
	int	exits;
	int	collects;
}	t_counts;

typedef struct s_flood
{
	char	**map;
	int		width;
	int		height;
}	t_flood;

typedef struct s_pathcheck
{
	int	px;
	int	py;
	int	total_collects;
	int	found_collects;
	int	found_exit;
}	t_pathcheck;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_w;
	int			map_h;
	int			player_count;
	int			exit_count;
	int			collect_count;
	int			player_x;
	int			player_y;
	int			collectibles;
	void		*img_wall;
	void		*img_floor;
	void		*img_player;
	void		*img_exit;
	void		*img_collect;
	t_player	player;
}	t_game;

/* ===== utils.c ===== */
void	print_error(char *message);
int		ft_strcmp(char *s1, char *s2);
void	free_map(char **map);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

/* ===== map.c ===== */
char	**read_map_file(const char *filname);
char	**load_map(const char *filename, t_game *game);
int		get_map_height(char **map);
int		get_map_width(char **map);

/* ===== validate.c ===== */
int		validate_map(t_game *game);

/* ===== validate_counts.c ===== */
int		check_counts(t_game *game);
void	*ft_memset(void *s, int c, size_t n);

/* ===== flood_fill.c ===== */
int		validate_paths(t_game *game);
void	ff_fill(t_flood *flood, int x, int y);
void	find_player_and_count(char **map, int *px, int *py, int *total);
int		count_reachable(t_game *game, char **map_cpy, int *found_exit);
int		check_path_result(int found, int total, int exit);
char	**dup_map(char **map);

/* ===== player.c ===== */
int		can_move_to(t_game *game, int x, int y);
void	move_player(t_game *game, int dx, int dy);

/* ===== hooks.c ===== */
int		handle_keypress(int keycode, t_game *game);
int		close_game(t_game *game);
void	setup_hooks(t_game *game);

/* ===== render.c ===== */
void	render_game(t_game *game);
void	load_images(t_game *game);
//void	put_tile(t_game *game, int x, int y, char c);
void	destroy_images(t_game *game);

/* ===== main.c ===== */
void	init_game(t_game *game);

#endif
