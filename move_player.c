/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:10:48 by achakour          #+#    #+#             */
/*   Updated: 2025/01/24 10:42:56 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub3d *strct, t_player *p)
{
	p->turn_speed = 45 * (PI / 2);
	p->move_speed = 10;
	p->up_down = 1;
	p->right_left = 0;
	p->parent = strct;
	p->x_pos =  1 * PXL + (PXL / 2);
	p->y_pos = 1 * PXL + (PXL / 2);
}

int check_wall(char **map ,float x, float y)
{
	// if ((x > 0 && x < WIN_WIDTH) && (y > 0 && y < WIN_HIGHT))
	// {
		if (map[(int)floor(x / PXL)][(int)floor(y / PXL)] == '1')
		{
			// printf("ENterd y = %d x = %d map %c\n", (int)floor(y / PXL), (int)floor(x / PXL), map[(int)floor(x / PXL)][(int)floor(y / PXL)]);
			// printf("ENterd\n");//(int)floor(y / PXL), (int)floor(x / PXL)
			return (0);
		}
		// printf("NOT ENterd y = %d x = %d map %c\n", (int)floor(y / PXL), (int)floor(x / PXL), map[(int)floor(x / PXL)][(int)floor(y / PXL)]);
		return (1);
	// }
	// return (0);
}

void	move_player(t_player *p)
{
	float	move_step;
	float	x;
	float	y;

	p->rotat_angle += p->right_left * p->turn_speed;
	move_step = p->up_down * p->move_speed;

	x = p->x_pos + cos(p->rotat_angle) * move_step;
	y = p->y_pos + sin(p->rotat_angle) * move_step;

	if (check_wall(p->map, x, y))
	{
		p->x_pos = x;
		p->y_pos = y;
	}
}

int	select_move(int keycode, t_cub3d *p)
{
	t_player	*plr;

	if (keycode == ESC || keycode == Q)
		ft_exit(p);
	plr = p->player;
	if (keycode == UP)
		plr->up_down = 1;
	else if (keycode == DOWN)
		plr->up_down = -1;
	else if (keycode == RIGHT)
		plr->right_left = 1;
	else if (keycode == LEFT)
		plr->right_left = -1;
	move_player(p->player);
	update_window(p);
	// ft_caster();
	return (1);
}
