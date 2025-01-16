/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:27 by achakour          #+#    #+#             */
/*   Updated: 2024/12/30 10:37:08 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *p)
{
	p->turn_speed = 45 * (PI / 2);
	p->move_speed = 100;
	p->up_down = 1;
	p->right_left = 1;
	
	if (p->up_down = 1)
		p->rotat_angle = 90;
	else if (p->up_down == -1)
		p->rotat_angle = 90 * 3;
	else if (p->right_left == -1)
		p->rotat_angle = 90 * 2
	else if (p->right_left == 1)
		p->rotat_angle = 0;
}

void	put_win(t_cub3d *p)
{
    int	fd;

	p->mlx = mlx_init();
	fd = open("map.txt", O_RDONLY);
    p->map = get_map(fd);
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
	move_player(p->wolf);
	mlx_loop(p->mlx);
}

void	move_player(t_player *p)
{
	float	move_step;
	float	x;
	float	y;

	p->rotat_angle += p->right_left * p->turn_speed;// * delta_time
	move_step = p->up_down * p->move_speed;// * delta_time

	x = p->x_pos + cos(p->rotat_angle) * move_step;
	y = p->y_pos + sin(p->rotat_angle) * move_step;

	if (check_wall(x, y))
	{
		p->x_pos = x;
		p->y_pos = y;
	}
}

int main()
{
    t_cub3d *p;
	t_player	*player;

	p = malloc(sizeof(t_cub3d));
	player = malloc(sizeof(t_player));
	init_player(player);
	p->wolf = player;
	put_win(p);
	return (0);
}
