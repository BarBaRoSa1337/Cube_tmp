/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:12:33 by achakour          #+#    #+#             */
/*   Updated: 2025/01/25 10:17:43 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    get_player_char(t_cub3d *p, int fd)
{
    int i;
    int j;
    char c;
    char **map;
    
    map = get_map(fd);
    i = 0;
    while (i < p->win_height)
    {
        j = 0;
        while (j < p->win_width)
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' ||
                    map[i][j] == 'W' || map[i][j] == 'E')
            {
                c = map[i][j];
                return (c);
            }
            ++j;
        }
        ++i;
    }
    // free_map(map);
}
