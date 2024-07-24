/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:06:14 by labdello          #+#    #+#             */
/*   Updated: 2024/07/24 17:58:54 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	isometric(t_point *point, int z)
{
	int	tmp;

	tmp = point->x;
	point->x = (tmp - point->y) * cos(0.523599);
	point->y = (tmp + point->y) * sin(0.523599) - z;
}

void	slope_bigger_than_one(t_delta d, t_point a, t_env *env)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * d.x - d.y;
	// put_pixel(a.x, a.y);
	mlx_pixel_put(env->mlx, env->win, a.x, a.y, 16777215);
	while (i < d.y)
	{
		a.y += 1;
		if (p < 0)
			p = p + 2 * d.x;
		else
		{
			a.x += 1;
			p = p + 2 * d.x - 2 * d.y;
		}
		mlx_pixel_put(env->mlx, env->win, a.x, a.y, 16777215);
		// put_pixel(a.x, a.y);
		i++;
	}
}

void	slope_less_than_one(t_delta d, t_point a, t_env *env)
{
	int	p;
	int	i;

	i = -1;
	p = 2 * abs(d.y) - abs(d.x);
	while (++i < abs(d.x))
	{
		if (d.x > 0)
			a.x += 1;
		else
			a.x -= 1;
		if (p < 0)
			p = p + 2 * abs(d.y);
		else
		{
			if (d.y > 0)
				a.y += 1;
			else
				a.y -= 1;
			p = p + 2 * abs(d.y) - 2 * abs(d.x);
		}
		// put_pixel(a.x, a.y);
		mlx_pixel_put(env->mlx, env->win, a.x, a.y, 16777215);
	}
}

void	draw_line(t_point a, t_point b, t_env *env)
{
	t_delta	d;

	a.x += WIDTH / 2;
	a.y += HEIGHT / 2;
	b.x += WIDTH / 2;
	b.y += HEIGHT / 2;
	d.x = b.x - a.x;
	d.y = b.y - a.y;
	if (ft_abs(d.x) > ft_abs(d.y))
		slope_less_than_one(d, a, env);
	else
		slope_bigger_than_one(d, a, env);
}

void	draw_map(t_env *env)
{
	int		x;
	int		y;
	t_point a;
	t_point b;

	x = 0;
	while (x < env->map->width)
	{
		y = 0;
		a.x = x;
		b.x = x + 1;
		while (y < env->map->height)
		{
			a.y = y;
			b.y = y;
			draw_line(a, b, env);
			b.x = x;
			b.y = y + 1;
			draw_line(a, b, env);
			// draw_line(x, y, x + 1, y);
			// draw_line(x, y, x, y + 1);
			y++;
		}
		x++;
	}
}
