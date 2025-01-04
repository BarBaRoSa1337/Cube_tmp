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
	p->x_pos = WIN_WIDTH / 2;
	p->y_pos = WIN_HEIGHT / 2;
	p->rad = 3;
	p->walk = 0;
	p->face = 0;
	p->rotat = PIE / 2;
	p->move_speed = 2.0;
	p->rotat_speed = 2 * (PI / 180);
}

// void	put_win(t_cub3d *p)
// {
//     int	fd;
	
// 	p->mlx = mlx_init();
// 	fd = open("map.txt", O_RDONLY);
//     p->map = get_map(fd);
// 	p->flour = (t_data *)malloc(sizeof(t_data));
// 	p->wall = (t_data *)malloc(sizeof(t_data));
// 	p->mlx_win = mlx_new_window(p->mlx, (39 * PXL), (16 * PXL),
// 			"cub3d");
// 	p->flour->img = mlx_new_image(p->mlx, PXL, PXL);
// 	p->wall->img = mlx_new_image(p->mlx, PXL, PXL);
// 	p->flour->addr = mlx_get_data_addr(p->flour->img, &p->flour->bits_per_pixel, &p->flour->line_length,
// 								&p->flour->endian);
// 	p->wall->addr = mlx_get_data_addr( p->wall->img, &p->wall->bits_per_pixel, &p->wall->line_length,
// 								&p->wall->endian);
// 	put_images(p);
// 	mlx_loop(p->mlx);
// }

int main()
{
    t_cub3d *p;
	t_player	*wolf;

	// wolf = malloc(sizeof(t_player));
	// init_player(wolf);
	p = malloc(sizeof(t_cub3d));
	put_win(p);
	return (0);
}
