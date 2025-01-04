/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:30 by achakour          #+#    #+#             */
/*   Updated: 2024/11/23 11:54:15 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//increment ray
//ray_ang = FOV / N_RAYS;

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

void	put_images(t_cub3d *s)
{
	char	**map;
	int		i;
	size_t	j;

	int grid_size = 50; // Size of each cell in pixels
	int cell_x = 5;     // Column 5
	int cell_y = 3;     // Row 3

	// Calculate the dot's position
	int x = cell_x * grid_size + (grid_size / 2);
	int y = cell_y * grid_size + (grid_size / 2);

	// Draw the dot
	// my_mlx_pixel_put(&img, x, y, 0xffffff);
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
			// {
			// 	my_mlx_pixel_put(s->flour, x - 1, y - 1 , 0x0000FF00);
			// 	my_mlx_pixel_put(s->flour, x, y , 0x0000FF00);
			// 	mlx_put_image_to_window(s->mlx, s->mlx_win, s->flour->img ,(j * PXL), (i * PXL));
			// 	// put_pixels(s);
			// }
			++j;
		}
		++i;
	}
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
