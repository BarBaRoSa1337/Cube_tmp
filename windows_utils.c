/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:30 by achakour          #+#    #+#             */
/*   Updated: 2025/01/24 10:55:18 by achakour         ###   ########.fr       */
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

void	*ft_exit(t_cub3d *p)
{
	exit(0);
}

void	init_win(t_cub3d *p)
{
	p->img = (t_data *)malloc(sizeof(t_data));
	p->mlx_win = mlx_new_window(p->mlx, (39 * PXL), (16 * PXL),
			"cub3d");
	p->img->img = mlx_new_image(p->mlx, (39 * PXL), (16 * PXL));
	p->img->addr = mlx_get_data_addr(p->img->img, &p->img->bits_per_pixel, &p->img->line_length,
								&p->img->endian);
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rect(t_data *img, float x, float y, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < PXL)
	{
		j = 0;
		while (j < PXL)
		{
			if (c == '0' || c == 'P')
				my_mlx_pixel_put(img ,x + i ,y + j , 0x3C00FF);
			else if (c == '1')
				my_mlx_pixel_put(img , (x + i) , (y + j), 0x00FF6F);
			++j;
		}
		++i;
	}
}

void DDA(t_data *p, int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
        my_mlx_pixel_put(p ,(int)round(X), (int)round(Y), 
                 0xFAFAFA); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
    } 
}

void	draw_player(t_cub3d *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(s->img ,s->player->y_pos - j , s->player->x_pos - i ,0xFAFAFA);
			++j;
		}
		++i;
	}
}

void	put_images(t_cub3d *s)
{
	char	**map;
	int		i;
	size_t	j;

	i = 0;
	map = s->map;
	while (i < 16)
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			draw_rect(s->img ,j * PXL, i * PXL , map[i][j]);
			++j;
		}
		++i;
	}
	draw_player(s);
	mlx_put_image_to_window(s->mlx, s->mlx_win, s->img->img, 0, 0);
}

void	update_window(t_cub3d *p)
{
	int	x;
	int y;

	x = p->player->x_pos;
	y = p->player->y_pos;
	mlx_clear_window(p->mlx, p->mlx_win);
	put_images(p);
	// DDA(p->img, x, y, x + cos(p->player->rotat_angle) * 40, y + sin(p->player->rotat_angle) * 40);
}
