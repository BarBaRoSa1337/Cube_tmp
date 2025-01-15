/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:36:33 by achakour          #+#    #+#             */
/*   Updated: 2025/01/15 13:19:25 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_direction(float angl, t_ray *ray)
{
	angl = remainder(angl, 2 * PI);
	if (ray->ray_angle > 0 && ray->ray_angle < PI)
		ray->up_dowm = -1;
	else
		ray->up_dowm = 1;
	if (ray->ray_angle < PI / 2 || ray->ray_angle > 1.5 * PI)
		ray->right_left = -1;
	else
		ray->right_left	= 1;
	if (angl < 0)
		angl = 2 * PI + angl;
	return (angl);
}

void	ft_cast_horz(t_cub3d *p, t_ray *ray, float ray_angl)
{
	float	frst_x;
	float	frst_y;

	ray_angl = calc_direction(ray_angl, ray);
	frst_y = floor(p->ray->y_pos / PXL) * PXL;
	if (ray->up_dowm == -1)
		frst_y += PXL;// (y = i) in the map representation

	frst_x = p->ray->x_pos + (frst_y - p->ray->y_pos) / tan(ray->ray_angle);
	ray->y_step = PXL;

	if (ray->up_dowm = 1)
		ray->y_step *= -1;

	ray->x_step = PXL / tan(ray->ray_angle);
	if ((ray->right_left == -1 && ray->x_step > 0) ||
			(ray->right_left == 1 && ray->x_step < 0))
		ray->x_step *= -1;
	ray->horz_x = frst_x;
	ray->horz_y = frst_y;
	while ((ray->hrz_x >= 0 && ray->hrz_x <= WIN_WIDTH) &&
		(ray->hrz_y >= 0 && ray->hrz_y <= WIN_HIGHT))
	{
		if (map[floor(ray->hrz_y / PXL)][floor(ray->hrz_x / PXL) + 1] == '1')
			break;
		else
		{
			ray->hrz_x += ray->x_step;
			ray->hrz_y += ray->y_step;
		}
	}
}

void	ft_cast_vert(t_cub3d *p, t_ray *ray, float ray_angl)
{
	float	frst_x;
	float	frst_y;

	ray_angl = calc_direction(ray_angl, ray);
	frst_x = floor(p->ray->x_pos / PXL) * PXL;
	if (ray->right_left == 1)
		frst_x += PXL;
		
	frst_y = p->ray->y_pos + (frst_x - p->ray->x_pos) * tan(ray->ray_angle);
	ray->x_step = PXL;
	if (ray->right_left = -1)
		ray->x_step *= -1;
		
	ray->y_step = PXL * tan(ray->ray_angle);
	if ((ray->up_dowm == 1 && ray->y_step > 0) ||
			(ray->up_dowm == -1 && ray->y_step < 0))
		ray->y_step *= -1;
	ray->hrz_x = frst_x;
	ray->hrz_y = frst_y;
	while ((ray->hrz_x >= 0 && ray->hrz_x <= WIN_WIDTH) &&
		(ray->hrz_y >= 0 && ray->hrz_y <= WIN_HIGHT))
	{
		if (map[floor(ray->hrz_y / PXL)][floor(ray->hrz_x / PXL) + 1] == '1')
		{
			break;
		}
		else
		{
			ray->hrz_x += ray->x_step;
			ray->hrz_y += ray->y_step;
		}
	}
}

// void	ft_get_distance(t_ray *p)
// {
// 	float	horz_dst;
// 	float	vert_dst;

// 	horz_dst = sqrt((x1 - x2)(x1 - x2) * (y1 - y2)(y1 - y2));
// 	vert_dst = sqrt((x1 - x2)(x1 - x2) * (y1 - y2)(y1 - y2));
// 	if (horz_dst < vert_dst)
// 	{
		
// 	}
// 	else
// 	{
		
// 	}
// }

void	ft_caster(t_cub3d *p)
{
	t_ray	*rays;
	float	ray_angle;
	int		i;

	i = 0;
	ray_angle = p->wolf->ray_angle - (FOV / 2);
	p->rays = malloc(sizeof(t_ray) * N_RAYS);
	while (i < N_RAYS)
	{
		ft_cast_horzn(p, p->rays[i], ray_angle);
        ft_cast_vert(p, p->rays[i], ray_angle);
		ft_get_distance(p->rays[i]);
		ray_angle += FOV / N_RAYS;
		++i;
	}
}
