/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:48:09 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/26 15:33:11 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	load_tex(t_data *data)
{
	t_map	*map;

	map = data->map;
	map->textures[0] = mlx_load_png(map->so);
	map->textures[1] = mlx_load_png(map->no);
	map->textures[2] = mlx_load_png(map->we);
	map->textures[3] = mlx_load_png(map->ea);
	map->textures[4] = mlx_load_png("textures/door.png");
	if (!map->textures[0] || !map->textures[1] || !map->textures[2]
		|| !map->textures[3] || !map->textures[4])
		exit(1);
}

float	calc_tex_x_vertical(t_ray *ray, float tex_width)
{
	float	tex_x;

	tex_x = ray->wall_hit_y;
	tex_x = fmod(tex_x, TILE_SIZE);
	if (tex_x < 0)
		tex_x += TILE_SIZE;
	tex_x = (tex_x * tex_width) / TILE_SIZE;
	if (ray->ray_facing_left)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

float	calc_tex_x_horizontal(t_ray *ray, float tex_width)
{
	float	tex_x;

	tex_x = ray->wall_hit_x;
	tex_x = fmod(tex_x, TILE_SIZE);
	if (tex_x < 0)
		tex_x += TILE_SIZE;
	tex_x = (tex_x * tex_width) / TILE_SIZE;
	if (!ray->ray_facing_up)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	_tex_x(t_ray *ray, float *tex_x, float tex_width)
{
	float	angle_correction;

	angle_correction = fabs(cos(ray->ray_angle - ray->ray_angle));
	*tex_x = fmod(*tex_x, TILE_SIZE);
	if (tex_x < 0)
		tex_x += TILE_SIZE;
	angle_correction = fabs(cos(ray->ray_angle - ray->ray_angle));
	*tex_x *= angle_correction;
	*tex_x = (*tex_x * tex_width) / TILE_SIZE;
}

float	get_tex_x(t_ray *ray, mlx_texture_t *tex)
{
	float	tex_x;
	float	tex_width;

	tex_width = (float)tex->width;
	if (ray->was_vert)
		tex_x = ray->wall_hit_y;
	else
		tex_x = ray->wall_hit_x;
	_tex_x(ray, &tex_x, tex_width);
	if (ray->was_vert)
	{
		if (ray->ray_facing_left)
			tex_x = tex_width - tex_x - 1;
	}
	else
	{
		if (!ray->ray_facing_up)
			tex_x = tex_width - tex_x - 1;
	}
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}
