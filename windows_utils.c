/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:30 by achakour          #+#    #+#             */
/*   Updated: 2025/01/23 09:51:36 by achakour         ###   ########.fr       */
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

void	draw_player(t_cub3d *p)
{
	my_mlx_pixel_put(p->flour, 20, 20, 0x0000FF00);
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->flour->img , (int)floor(p->player->x_pos / PXL), (int)floor(p->player->y_pos / PXL));
}

void	put_images(t_cub3d *s)
{
	char	**map;
	int		i;
	size_t	j;
	
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
			// else if (map[i][j] == 'P')
			// 	map[i][j] = '0';
			++j;
		}
		++i;
	}
	draw_player(s);
}

void	update_window(t_cub3d *p)
{
	char	**map;
	int		i;
	size_t	j;

	i = 0;
	map = p->map;
	put_pixels(p);
	while (i < 16)
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == '0' || map[i][j] == 'P')
				mlx_put_image_to_window(p->mlx, p->mlx_win, p->flour->img, (j * PXL), (i * PXL));
			else if (map[i][j] == '1')
				mlx_put_image_to_window(p->mlx, p->mlx_win, p->wall->img ,(j * PXL), (i * PXL));
			++j;
		}
		++i;
	}
	draw_player(p);
}

void	*ft_exit(t_cub3d *p)
{
	exit(0);
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
	put_images(p);
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
