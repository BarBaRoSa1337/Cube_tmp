/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:30 by achakour          #+#    #+#             */
/*   Updated: 2025/01/29 09:45:21 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// double deg2rad(double deg)
// {
// 	return deg * (__pie__ / 180.0);
// }

// double	rad2deg(double rad)
// {
// 	return rad * (180.0 / __PIE__);
// }

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


void	*ft_exit(t_cub3d *p)
{
	exit(0);
}

void	init_win(t_cub3d *p)
{
	p->img = (t_data *)malloc(sizeof(t_data));
	p->mlx_win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HIGHT, "cub3d");
	p->img->img = mlx_new_image(p->mlx, WIN_WIDTH, WIN_HIGHT);
	p->img->addr = mlx_get_data_addr(p->img->img, &p->img->bits_per_pixel, 
									&p->img->line_length, &p->img->endian);
	put_images(p);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rect(t_data *img, float x, float y, char c)
{
	int	i, j;

	for (i = 0; i < PXL; i++)
	{
		for (j = 0; j < PXL; j++)
		{
			if (c == '0' || c == 'P')
				my_mlx_pixel_put(img, x + i, y + j, 0x3C00FF);  // Floor color
			else if (c == '1')
				my_mlx_pixel_put(img, x + i, y + j, 0x00FF6F);  // Wall color
		}
	}
}

void	DDA(t_data *p, int X0, int Y0, int X1, int Y1) 
{ 
	int dx = X1 - X0; 
	int dy = Y1 - Y0; 
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 

	if (steps == 0) {
		my_mlx_pixel_put(p, X0, Y0, 0xFAFAFA); 
		return;
	}

	float Xinc = dx / (float)steps; 
	float Yinc = dy / (float)steps; 
	float X = X0, Y = Y0; 

	for (int i = 0; i <= steps; i++) 
	{ 
		my_mlx_pixel_put(p, (int)X, (int)Y, 0xFAFAFA); 
		X += Xinc;  
		Y += Yinc;  
	} 
}

void	draw_player(t_cub3d *s)
{
	int	i, j;

	for (i = -5; i < 5; i++)
	{
		for (j = -5; j < 5; j++)
		{
			my_mlx_pixel_put(s->img, s->player->x_pos + i, s->player->y_pos + j, 0xFAFAFA);
		}
	}
}

void	put_images(t_cub3d *s)
{
	char	**map = s->map;
	int		i;
	size_t	j;

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < ft_strlen(map[i]); j++)
		{
			draw_rect(s->img, j * PXL, i * PXL, map[i][j]);
		}
	}
	draw_player(s);
	mlx_put_image_to_window(s->mlx, s->mlx_win, s->img->img, 0, 0);
}

void	update_window(t_cub3d *p)
{
	mlx_clear_window(p->mlx, p->mlx_win);
	put_images(p);
	DDA(p->img, p->player->x_pos, p->player->y_pos,
		p->player->x_pos + cos(p->player->rotat_angle) * 40, 
		p->player->y_pos + sin(p->player->rotat_angle) * 40);
}

