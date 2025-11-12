
#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../mlx/mlx.h"

# define TILE_SIZE 64
# define WIN_TITLE "so_long - bonus"
# define ENEMY_MOVE_DELAY 60  // Frames entre movimentos dos inimigos
# define ENEMY_START_DELAY 180 // Frames antes do primeiro movimento

// Estrutura de animação
typedef struct s_anim
{
	void	*frames[8];
	int		current;
	int		frame_count;
}	t_anim;

// Estrutura do jogador (modificada)
typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		direction;
	t_anim	anim;
}	t_player;

// Estrutura de inimigo
typedef struct s_enemy
{
	int		x;
	int		y;
	int		direction;
	t_anim	anim;
}	t_enemy;

// Estrutura do jogo (modificada)
typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_w;
	int			map_h;
	int			collectibles;
	t_player	player;
	t_enemy		*enemies;
	int			enemy_count;
	int			player_count;
	int			exit_count;
	int			collect_count;
	void		*img_floor;
	void		*img_wall;
	void		*img_player;
	void		*img_exit;
	void		*img_collect;
	void		*img_enemy;
	int			frame_counter;
}	t_game;

// Estruturas auxiliares (mesmas do mandatório)
typedef struct s_flood
{
	char	**map;
	int		width;
	int		height;
}	t_flood;

typedef struct s_counts
{
	int	players;
	int	exits;
	int	collects;
}	t_counts;

typedef struct s_pathcheck
{
	int	px;
	int	py;
	int	total_collects;
	int	found_collects;
	int	found_exit;
}	t_pathcheck;

// Funções mandatórias (mesmas)
void	init_game(t_game *game);
char	**load_map(const char *filename, t_game *game);
int		validate_map(t_game *game);
void	render_game(t_game *game);
void	move_player(t_game *game, int dx, int dy);
int		handle_keypress(int keycode, t_game *game);
int		close_game(t_game *game);
void	setup_hooks(t_game *game);
void	load_images(t_game *game);
void	destroy_images(t_game *game);
void	print_error(char *message);
void	free_map(char **map);
int		get_map_width(char **map);
int		get_map_height(char **map);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		check_counts(t_game *game);
int		validate_paths(t_game *game);
void	ff_fill(t_flood *flood, int x, int y);
char	**dup_map(char **map);
void	find_player_and_count(char **map, int *px, int *py, int *total);
int		count_reachable(t_game *game, char **map_cpy, int *found_exit);
int		check_path_result(int found, int total, int exit);
char	**read_map_file(const char *filename);
char	**split_map(char *buf);
void	*ft_memset(void *s, int c, size_t n);

// Funções BÔNUS (novas)
void	load_player_animations(t_game *game);
void	load_enemy_animations(t_game *game);
void	*get_player_sprite(t_game *game);
void	*get_enemy_sprite(t_game *game, int enemy_idx);
void	init_enemies(t_game *game);
void	move_enemies(t_game *game);
void	render_moves(t_game *game);
int		game_loop(t_game *game);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	destroy_animations(t_game *game);

#endif
