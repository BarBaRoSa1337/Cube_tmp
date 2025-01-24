/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:27 by achakour          #+#    #+#             */
/*   Updated: 2025/01/23 11:48:30 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	plug_play(t_cub3d *p)
{
	p->mlx = mlx_init();
    p->map = get_map(open("map.txt", O_RDONLY));
	p->player->map = p->map;
	init_win(p);
	mlx_hook(p->mlx_win, 2, 1L << 0, select_move, p);
	mlx_hook(p->mlx_win, 17, 0, ft_exit, p);
	mlx_loop(p->mlx);
}

int main()
{
	t_player	*wolf_stein;
    t_cub3d		*p;

	p = malloc(sizeof(t_cub3d));
	wolf_stein = malloc(sizeof(t_player));
	init_player(p, wolf_stein);
	p->player = wolf_stein;
	plug_play(p);
	return (0);
}
