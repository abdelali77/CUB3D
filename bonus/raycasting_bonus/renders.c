/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:46:39 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 16:22:51 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	clear_image(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while ((uint32_t)y < img->height)
	{
		x = 0;
		while ((uint32_t)x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	color_cell(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;
	int	start_x;
	int	start_y;

	start_x = data->player->pl->instances->x
		- (MINIMAP_SIZE / 2) / SCALE_FACTOR;
	start_y = data->player->pl->instances->y
		- (MINIMAP_SIZE / 2) / SCALE_FACTOR;
	map_x = start_x + (x / SCALE_FACTOR);
	map_y = start_y + (y / SCALE_FACTOR);
	if (data->map->map[map_y / TILE_SIZE][map_x / TILE_SIZE] == '1')
		mlx_put_pixel(data->map->mini_map, x, y, COLOR_WALL);
	if (data->map->map[map_y / TILE_SIZE][map_x / TILE_SIZE] == 'D'
		|| data->map->map[map_y / TILE_SIZE][map_x / TILE_SIZE] == 'O')
		mlx_put_pixel(data->map->mini_map, x, y, get_rgb(119, 141, 169, 255));
}

void	draw_minimap(t_data *data, int start_x, int start_y)
{
	int	y;
	int	x;
	int	map_x;
	int	map_y;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			map_x = start_x + (x / SCALE_FACTOR);
			map_y = start_y + (y / SCALE_FACTOR);
			if (map_x >= 0 && map_x < data->map->width && map_y >= 0
				&& map_y < data->map->height
				&& map_x / TILE_SIZE
				<= ft_strlen(data->map->map[map_y / TILE_SIZE]))
				color_cell(data, x, y);
		}
	}
}

void	render_minimap(t_data *data)
{
	int	visible_start_x;
	int	visible_start_y;
	int	x;
	int	y;

	if (data->map->mini_map)
		mlx_delete_image(data->map->mlx, data->map->mini_map);
	data->map->mini_map = mlx_new_image(data->map->mlx,
			MINIMAP_SIZE, MINIMAP_SIZE);
	mlx_image_to_window(data->map->mlx, data->map->mini_map, 10,
		WIN_HEIGHT - MINIMAP_SIZE - 10);
	visible_start_x = data->player->pl->instances->x
		- (MINIMAP_SIZE / 2) / SCALE_FACTOR;
	visible_start_y = data->player->pl->instances->y
		- (MINIMAP_SIZE / 2) / SCALE_FACTOR;
	draw_minimap(data, visible_start_x, visible_start_y);
	y = -1;
	while (++y < 3)
	{
		x = -1;
		while (++x < 3)
			mlx_put_pixel(data->map->mini_map, (MINIMAP_SIZE / 2) + x,
				(MINIMAP_SIZE / 2) + y, MAIN_COLOR);
	}
}
