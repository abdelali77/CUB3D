/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:45:56 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/13 12:12:46 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
# define CUB3_H

#include <stdio.h>
#include "./lib/lib.h"
#include "./getnextline/get_next_line.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>   
#include <float.h>
#include "./MLX42/include/MLX42/MLX42.h"

#define TILE_SIZE 64
#define COLOR_GREEN 0x0F000FF
#define MAIN_COLOR 0x0098FF98
#define COLOR_WALL 0x6468699B
#define COLOR_SPACE 0x37373737
#define PI 3.14159265358979323846
#define WALL_STRIP_WIDTH 1
// #define LINE_LENGTH 30
#define MINIMAP_SCALE_FACTOR 0.2

typedef struct	s_player {
	float	x;
	float	y;
	int		turn_direction;
	int		walk_direction;
	bool	walk;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	float	side_angle;
	double	FOV;
	mlx_image_t	*pl;
	mlx_image_t	*ray;
}				t_player;

typedef struct	s_ray
{
	float	wall_hit_X;
	float	wall_hit_Y;
	float	distance;
	float	ray_angle;
	int		ray_facing_down;
	int		ray_facing_up;
	int		ray_facing_right;
	int		ray_facing_left;
	bool	was_vert;
}				t_ray;

typedef struct s_map
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    int *floor_rgb;
    int *ciel_rgb;
    char **map;
    int player_x;
    int player_y;
    int HEIGHT;
    int WIDHT;
	mlx_t	*mlx;
	mlx_image_t	*mini_map;
	mlx_image_t	*img;
} t_map;

typedef struct	s_data
{
	t_map		*map;
	t_player	*player;
	t_ray		*rays;
}				t_data;


//config
void free_fc(char **fc);
void fre_maplines(char **map);
void free_map(t_map *map);
void ft_exit(char *str ,t_map *map);


void store_textures(char index, char *line, t_map **map);
int check_texture_perm(char *path);


void store_FC(char **fc, int flag, t_map **map);
int check_fc_prototype(char *line, t_map *map);
int check_FC(char *line, t_map *map);
void fill_colors(char *line, t_map **map, int flag);

void print_map(t_map *map);
void print_maplines(char **map);



int check_extension(char *file_name);
int check_positions(char *line, char f, char s, t_map **map);
int check_identif(char *line);
int check_color(char *fc, t_map *map);

//init
void null_init(t_map *map);
void init_floor(t_map **map);
void init_ciel(t_map **map);

//is_valid
int valide_color(char **fc, t_map *map);
int valid_color(char *line);
int valid_map(char *line);


//check_map
int check_map_walls(char **map);
void check_filled_map(t_map *map);
void check_ones(char *line);
int check_map_chars(char **map);
void check_zeros(t_map *map, int i, int j);
void check_map_spaces(t_map *map);


//read map
void read_map(char *file_name, t_map **map);

//parse
void parse_colors(char *line, t_map **map);
int is_map(char *line);
int empty_line(char *line);
int wall(char *map);
void WHXY(t_map **map);

//fill map
void fill_mapline(int map_line, int fd, t_map **map);
void fill_map(int fd, char *file_namp, t_map **map);

//map line
int lines_count(int fd, t_map *map);
int map_lines(int fd, t_map *map);



void	player_init(t_player *pl, t_data *data);
int		is_collision(t_data *data, float new_X, float new_Y);
void	render_3d_projection_walls(t_ray **rays, t_data *data);
void	draw_rectangle(mlx_image_t *img, int x, int y, int width, int height, uint32_t color);
t_ray	**cast_all_rays(t_data *data);
t_ray	*create_Ray(float angle);
void	cast_rays(t_ray *ray, t_data *data);
double	distance_between_2_points(int32_t x1, int32_t y1, float x2, float y2);
void	render_rays(t_data *data, float x1, float y1);
void	clear_image(mlx_image_t *img);
float	normalize_angle(float angle);
int		is_WALL(t_data *data, int x, int y);
void	render_map(t_map *map);
int		raycast(t_data *data);

#endif
