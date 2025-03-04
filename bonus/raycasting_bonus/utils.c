/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:09:34 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 16:02:51 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

int	is_wall(t_data *data, int x, int y)
{
	int	x_index;
	int	y_index;

	if (x < 0 || x >= data->map->width || y < 0 || y >= data->map->height)
		return (1);
	y_index = floor(y / TILE_SIZE);
	x_index = floor(x / TILE_SIZE);
	if (y_index >= data->map->height / TILE_SIZE
		|| x_index >= data->map->width / TILE_SIZE)
		return (1);
	if (x_index >= ft_strlen(data->map->map[y_index]))
		return (1);
	if (data->map->map[y_index][x_index] == '1')
		return (1);
	return (0);
}

int	is_door(t_data *data, int x, int y)
{
	int	x_index;
	int	y_index;

	if (x < 0 || x >= data->map->width || y < 0 || y >= data->map->height)
		return (1);
	y_index = floor(y / TILE_SIZE);
	x_index = floor(x / TILE_SIZE);
	if (y_index >= data->map->height / TILE_SIZE
		|| x_index >= data->map->width / TILE_SIZE)
		return (1);
	if (x_index >= ft_strlen(data->map->map[y_index]))
		return (1);
	if (data->map->map[y_index][x_index] == 'D')
		return (1);
	return (0);
}

int	is_collision(t_data *data, double new_x, double new_y)
{
	if (is_wall(data, new_x - TILE_SIZE / 4, new_y - TILE_SIZE / 4)
		|| is_wall(data, new_x + TILE_SIZE / 4, new_y - TILE_SIZE / 4)
		|| is_wall(data, new_x - TILE_SIZE / 4, new_y + TILE_SIZE / 4)
		|| is_wall(data, new_x + TILE_SIZE / 4, new_y + TILE_SIZE / 4))
		return (1);
	if (is_door(data, new_x - TILE_SIZE / 12, new_y - TILE_SIZE / 12)
		|| is_door(data, new_x + TILE_SIZE / 12, new_y - TILE_SIZE / 12)
		|| is_door(data, new_x - TILE_SIZE / 12, new_y + TILE_SIZE / 12)
		|| is_door(data, new_x + TILE_SIZE / 12, new_y + TILE_SIZE / 12))
		return (1);
	return (0);
}

double	dst_2_pts(int32_t x1, int32_t y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	normalize_angle(double angle)
{
	double	ret;

	ret = remainder(angle, (2 * M_PI));
	if (ret < 0)
		ret += (2 * M_PI);
	return (ret);
}
