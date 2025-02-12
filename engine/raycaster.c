/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:36:33 by achakour          #+#    #+#             */
/*   Updated: 2025/01/29 09:59:39 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float calc_direction(float angl, t_ray *ray) {
    angl = fmod(angl, 2 * PI);
    if (angl < 0)
        angl += 2 * PI;

    ray->up_dowm = (sin(angl) >= 0) ? 1 : -1;
    ray->right_left = (cos(angl) >= 0) ? 1 : -1;

    return angl;
}

void ft_cast_horz(t_cub3d *p, t_ray *ray, float ray_angl) {
    float frst_x, frst_y, next_x, next_y;

    ray->ray_angle = calc_direction(ray_angl, ray);

    frst_y = floor(p->player->y_pos / PXL) * PXL;
    if (ray->up_dowm == 1)
        frst_y += PXL;

    frst_x = p->player->x_pos + (frst_y - p->player->y_pos) / (tan(ray->ray_angle) + 1e-6);

    ray->y_step = PXL * ray->up_dowm;
    ray->x_step = (PXL / (fabs(tan(ray->ray_angle)) + 1e-6)) * ray->right_left;

    next_x = frst_x;
    next_y = frst_y;

    while (next_x >= 0 && next_x < WIN_WIDTH && next_y >= 0 && next_y < WIN_HIGHT) {
        int map_x = (int)(next_x / PXL);
        int map_y = (int)((next_y + (ray->up_dowm == -1 ? -1 : 0)) / PXL);
        
        if (p->map[map_y][map_x] == '1') {
            ray->hrz_x = next_x;
            ray->hrz_y = next_y;
            ray->found_hrz = 1;
            return;
        }
        next_x += ray->x_step;
        next_y += ray->y_step;
    }
    ray->found_hrz = 0;
}

void ft_cast_vert(t_cub3d *p, t_ray *ray, float ray_angl) {
    float frst_x, frst_y, next_x, next_y;

    ray->ray_angle = calc_direction(ray_angl, ray);

    frst_x = floor(p->player->x_pos / PXL) * PXL;
    if (ray->right_left == 1)  
        frst_x += PXL;

    frst_y = p->player->y_pos + (frst_x - p->player->x_pos) * (tan(ray->ray_angle) + 1e-6);

    ray->x_step = PXL * ray->right_left;
    ray->y_step = (PXL * fabs(tan(ray->ray_angle) + 1e-6)) * ray->up_dowm;

    next_x = frst_x;
    next_y = frst_y;

    while (next_x >= 0 && next_x < WIN_WIDTH && next_y >= 0 && next_y < WIN_HIGHT) {
        int map_x = (int)((next_x + (ray->right_left == -1 ? -1 : 0)) / PXL);
        int map_y = (int)(next_y / PXL);
        
        if (p->map[map_y][map_x] == '1') {
            ray->ver_x = next_x;
            ray->ver_y = next_y;
            ray->found_vrt = 1;
            return;
        }
        next_x += ray->x_step;
        next_y += ray->y_step;
    }
    ray->found_vrt = 0;
}

float calc_dist(float x1, float x2, float y1, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void get_distance(t_data *img, t_player *plr, t_ray *ray) {
    float horz_dst = (ray->found_hrz) ? calc_dist(plr->x_pos, ray->hrz_x, plr->y_pos, ray->hrz_y) : INFINITY;
    float vert_dst = (ray->found_vrt) ? calc_dist(plr->x_pos, ray->ver_x, plr->y_pos, ray->ver_y) : INFINITY;

    if (horz_dst < vert_dst) {
        ray->distance = horz_dst;
        ray->x_step = ray->hrz_x;
        ray->y_step = ray->hrz_y;
    } else {
        ray->distance = vert_dst;
        ray->x_step = ray->ver_x;
        ray->y_step = ray->ver_y;
    }
    DDA(img, plr->x_pos, plr->y_pos, ray->x_step, ray->y_step);
}

void ft_caster(t_cub3d *p) {
    p->n_rays = p->win_width / 4;
    p->rays = malloc(sizeof(t_ray) * p->n_rays);
    if (!p->rays)
        return;

    float ray_angle = p->player->rotat_angle - (FOV / 2);
    for (int i = 0; i < p->n_rays; i++) {
        t_ray *ray = &p->rays[i];

        ft_cast_horz(p, ray, ray_angle);
        ft_cast_vert(p, ray, ray_angle);
        get_distance(p->img, p->player, ray);
        ray_angle += (FOV / p->n_rays);
    }
}
