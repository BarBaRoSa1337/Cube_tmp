/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:30 by achakour          #+#    #+#             */
/*   Updated: 2025/01/17 09:49:13 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double deg2rad(double deg)
// {
// 	return deg * (__pie__ / 180.0);
// }

// double	rad2deg(double rad)
// {
// 	return rad * (180.0 / __PIE__);
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int check_wall(char **map ,float x, float y)
{
	if ((x > 0 && x < WIN_WIDTH) && (y > 0 && y < WIN_HIGHT))
	{
		if (map[(int)floor(y / PXL)][(int)floor(x / PXL)] == 1)
			return (0);
		return (1);
	}
	return (0);
}

void	put_images(t_cub3d *s)
{
	char	**map;
	int		i;
	size_t	j;

	// Calculate the dot's position
	int x = s->wolf->x_pos * PXL + (PXL / 2);
	int y = s->wolf->y_pos * PXL + (PXL / 2);

	i = 0;
	map = s->map;
	put_pixels(s);
	while (i < 16)
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == '0')
				mlx_put_image_to_window(s->mlx, s->mlx_win, s->flour->img, (j * PXL), (i * PXL));
			else if (map[i][j] == '1')
				mlx_put_image_to_window(s->mlx, s->mlx_win, s->wall->img ,(j * PXL), (i * PXL));
			else if (map[i][j] == 'P')
			{
				// my_mlx_pixel_put(s->flour->img, 25, 25, 0xffffff);
				mlx_put_image_to_window(s->mlx, s->mlx_win, s->flour->img ,(j * PXL), (i * PXL));
				// put_pixels(s);
			}
			++j;
		}
		++i;
	}
}

void	ft_exit(t_cub3d *p)
{
	exit(0);
}

int	select_move(int keycode, t_cub3d *p)
{
	t_player	*plr;

	if (keycode == ESC || keycode == Q)
		ft_exit(p);
	plr = p->wolf;
	if (keycode == UP)
		plr->up_down = 1;
	else if (keycode == DOWN)
		plr->up_down = -1;
	else if (keycode == RIGHT)
		plr->right_left = 1;
	else if (keycode == LEFT)
		plr->right_left = -1;
	return (1);
}

void	put_pixels(t_cub3d	*p)
{
	int	j;
	int	i;

	i = -1;
	while (++i < PXL)
	{
		j = -1;
		while (++j < PXL)
			my_mlx_pixel_put(p->wall, i, j , 0x00FF0000);
	}
	i = -1;
	while (++i < PXL)
	{
		j = -1;
		while (++j < PXL)
			my_mlx_pixel_put(p->flour, i , j , 808080);
	}
}

void	init_win(t_cub3d *p)
{
	p->flour = (t_data *)malloc(sizeof(t_data));
	p->wall = (t_data *)malloc(sizeof(t_data));
	p->mlx_win = mlx_new_window(p->mlx, (39 * PXL), (16 * PXL),
			"cub3d");
	p->flour->img = mlx_new_image(p->mlx, PXL, PXL);
	p->wall->img = mlx_new_image(p->mlx, PXL, PXL);
	p->flour->addr = mlx_get_data_addr(p->flour->img, &p->flour->bits_per_pixel, &p->flour->line_length,
								&p->flour->endian);
	p->wall->addr = mlx_get_data_addr( p->wall->img, &p->wall->bits_per_pixel, &p->wall->line_length,
								&p->wall->endian);
}

char	**get_map(int fd)
{
	char	**map;
	char	*buff;
	char	*tmp;

	tmp = get_next_line(fd);
	buff = NULL;
	while (tmp)
	{
		if (tmp[0] == '\n')
			return (free(buff), NULL);
		buff = ft_strjoin(buff, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	buff = ft_strjoin(buff, "\n");
	map = ft_split(buff, '\n');
	return (free(buff), map);
}
