/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:24 by achakour          #+#    #+#             */
/*   Updated: 2025/01/02 10:10:02 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

# define UP 119
# define DOWN 115
# define RIGHT 100
# define LEFT 97
# define ESC 65307
# define Q 113
#define BUFFER_SIZE 13
#define PXL 40
#define WIN_WIDTH 300
#define PI 3.14159
#define N_RAYS = WIN_WIDHT / 4
#define WIN_HIGHT
#define FOV  60 * (PIE / 180.0)


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ray {
	int		up_dowm;// 1 for up -1 for down
	int		right_left;//1 for right -1 for left
	float	distance;
	float	ray_angle;
	float	hrz_x;
	float	hrz_y;
	float	ver_x;
	float	ver_y;
	float	x_step;
	float	y_step;
}	t_ray;

typedef struct s_player
{
	char	**map;
	int		x_pos;
	int		y_pos;
    int     up_down;
    int   right_left;
    float   move_speed;
    float   rotat_angle;
	float turn_speed;
} t_player;

typedef struct s_cub3d
{
	t_data	*wall;
	t_data	*flour;
	t_ray	*rays;
	t_player	*wolf;
    int     height;
    char	**map;
	int		img_w;
	int		img_h;
    int     wide;
	void	*mlx;
	void	*mlx_win;
	void	*win;
	int		fd;
}   t_cub3d;


void	ft_strlcpy(char *dst, char *src, size_t dstsize);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
char	*ft_strdup(char *str);
void	put_pixels(t_cub3d	*p);
int check_wall(char **map ,float x, float y);
void	put_images(t_cub3d *s);
int	select_move(int keycode, t_cub3d *p);
void	init_win(t_cub3d *p);
char	**ft_split(char const *s, char c);
char	**get_map(int fd);
int	    ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif