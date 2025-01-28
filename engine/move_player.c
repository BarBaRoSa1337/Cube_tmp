/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:10:48 by achakour          #+#    #+#             */
/*   Updated: 2025/01/28 12:44:14 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_cub3d *strct, t_player *p)
{
	strct->win_width = 200;
	p->rotat_angle = PI / 2;
	p->turn_speed = 45 * (PI / 2);
	p->move_speed = 10;
	p->up_down = 0;
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

	p->rotat_angle = remainder(p->rotat_angle, 2 * PI);
    if (p->rotat_angle < 0)
        p->rotat_angle += 2 * PI;
	p->rotat_angle += p->right_left * p->turn_speed;
	move_step = p->up_down * p->move_speed;

	x = p->x_pos + cos(p->rotat_angle) * move_step;
	y = p->y_pos + sin(p->rotat_angle) * move_step;

	if (check_wall(p->map, x, y))
	{
		printf("okld %f\n", p->x_pos);
		p->x_pos = x;
		printf("nes %f\n", p->x_pos);
		p->y_pos = y;
	}
}

void	move_side(t_player *p)
{
	float	move_step;
	float	x;
	float	y;

	p->rotat_angle = remainder(p->rotat_angle, 2 * PI);
    if (p->rotat_angle < 0)
        p->rotat_angle += 2 * PI;
	// p->rotat_angle += p->right_left * p->turn_speed;
	move_step = p->right_left * p->move_speed;

	x = p->x_pos + cos(p->rotat_angle + PI / 2) * move_step;
	y = p->y_pos + sin(p->rotat_angle + PI / 2) * move_step;

	if (check_wall(p->map, x, y))
	{
		p->x_pos = x;
		p->y_pos = y;
	}
}

int	game_loop(int keycode, t_cub3d *p)
{
	if (keycode == 65363 || keycode == 65361)
		move_side(p->player);
	else
		move_player(p->player);
	update_window(p);
	ft_caster(p);
	p->player->right_left = 0;
	p->player->up_down = 0;
	return (1);
}

int	select_move(int keycode, t_cub3d *p)
{
	if (keycode == ESC)
		ft_exit(p);
	if (keycode == UP || keycode == 65362)
		p->player->up_down = 1;
	else if (keycode == DOWN || keycode == 65364)
		p->player->up_down = -1;
	else if (keycode == RIGHT || keycode == 65363)
		p->player->right_left = -1;
	else if (keycode == LEFT || keycode == 65361)
		p->player->right_left = 1;
	game_loop(keycode, p);
	return (1);
}

int	release_key(t_cub3d *p)
{
	p->player->right_left = 0;
	p->player->up_down = 0;
	return (1);
}
