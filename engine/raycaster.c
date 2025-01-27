/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:36:33 by achakour          #+#    #+#             */
/*   Updated: 2025/01/27 12:11:15 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	float	next_x;
	float	next_y;

	frst_x = 0;
	frst_y = 0;
	ray->ray_angle = calc_direction(ray_angl, ray);
	frst_y = floor(p->player->y_pos / PXL) * PXL;
	if (ray->up_dowm == -1)
		frst_y += PXL;// (y = i) in the map representation

	frst_x = p->player->x_pos + (frst_y - p->player->y_pos) / tan(ray->ray_angle);
	ray->y_step = PXL;

	if (ray->up_dowm == 1)
		ray->y_step *= -1;

	ray->x_step = PXL / tan(ray->ray_angle);
	if ((ray->right_left == -1 && ray->x_step > 0) ||
			(ray->right_left == 1 && ray->x_step < 0))
		ray->x_step *= -1;
	next_x = frst_x;
	next_y= frst_y;
	while ((next_x >= 0 && next_x <= WIN_WIDTH) &&
		(next_y >= 0 && next_y <= WIN_HIGHT))
	{
		if (p->map[(int)floor(next_y / PXL)][(int)floor(next_x / PXL) + 1] == '1')
		{
			ray->hrz_x = ray->x_step;
			ray->hrz_y = ray->y_step;
			ray->found_hrz = 1;
			break;
		}
		else
		{
			next_x += ray->x_step;
			next_y += ray->y_step;
		}
	} 
}

void	ft_cast_vert(t_cub3d *p, t_ray *ray, float ray_angl)
{
	float	frst_x;
	float	frst_y;
	float	next_x;
	float	next_y;

	frst_x = 0;
	frst_y = 0;
	ray->ray_angle = calc_direction(ray_angl, ray);
	frst_x = floor(p->player->x_pos / PXL) * PXL;
	if (ray->right_left == 1)
		frst_x += PXL;
		
	frst_y = p->player->y_pos + (frst_x - p->player->x_pos) * tan(ray->ray_angle);
	ray->x_step = PXL;
	if (ray->right_left == -1)
		ray->x_step *= -1;
		
	ray->y_step = PXL * tan(ray->ray_angle);
	if ((ray->up_dowm == 1 && ray->y_step > 0) ||
			(ray->up_dowm == -1 && ray->y_step < 0))
		ray->y_step *= -1;
	next_x = frst_x;
	next_y= frst_y;
	while ((next_x >= 0 && next_x <= WIN_WIDTH) &&
		(next_y >= 0 && next_y <= WIN_HIGHT))
	{
		if (p->map[(int)floor(next_y / PXL)][(int)floor(next_x / PXL) + 1] == '1')
		{
			ray->ver_x = ray->x_step;
			ray->ver_y = ray->y_step;
			// ray->found_vrt = 1;
			break;
		}
		else
		{
			next_x += ray->x_step;
			next_y += ray->y_step;
		}
	} 
}

void	get_distance(t_ray *p)
{
	float	horz_dst;
	float	vert_dst;

	if (p->found_hrz)
		horz_dst = calc_dist(p->, p->hrz_x, p->, p->hrz_y);
	else if (p->found_vrt)
		vert_dst = calc_dist(p-> , p->ver_x, p-> , p->ver_y);
	if (p->ver_x < p->hrz_x)
		p->x_step = p->ver_x;
	else
		p->x_step = p->hrz_x;
	if (p->ver_y < p->hrz_y)
		p->y_step = p->ver_y;
	else
		p->y_step = p->hrz_y;
	if (horz_dst < vert_dst)
	{
		p->distance = horz_dst;
	}
	else
	{
		p->distance = vert_dst;
	}
	DDA(, player_x, player_y, p->x_step, p->y_step);
}

void	ft_caster(t_cub3d *p)
{
	int		i;
	t_ray	*rays;
	float	ray_angle;

	i = 0;
	p->n_rays = p->win_width / 4;
	ray_angle = p->player->rotat_angle - (FOV / 2);
	p->rays = malloc(sizeof(t_ray) * p->n_rays);
		printf("n %d\n", p->n_rays); 
	while (i < p->n_rays)
	{
		ft_cast_horz(p, &p->rays[i], ray_angle);
        ft_cast_vert(p, &p->rays[i], ray_angle);
		// get_distance(&p->rays[i]);
		ray_angle += FOV / p->n_rays;
		++i;
	}
}
