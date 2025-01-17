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
	printf("player pos: %f %f\n", p->x_pos,p->y_pos);
}

void	plug_play(t_cub3d *p)
{
	p->mlx = mlx_init();
    p->map = get_map(open("map.txt", O_RDONLY));
	init_win(p);
	put_images(p);
	mlx_hook(p->mlx_win, 2, 1L << 0, select_move, p);
	// mlx_hook(p->mlx_win, 17, 0, ft_exit, p);
	move_player(p->wolf);
	mlx_loop(p->mlx);
}

int main()
{
    t_cub3d *p;
	t_player	*player;

	p = malloc(sizeof(t_cub3d));
	player = malloc(sizeof(t_player));
	init_player(player);
	p->wolf = player;
	plug_play(p);
	return (0);
}
