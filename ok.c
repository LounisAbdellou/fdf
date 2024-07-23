/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:27:35 by labdello          #+#    #+#             */
/*   Updated: 2024/07/24 15:32:55 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

a->x *= zoom;
b->x *= zoom;
a->y *= zoom;
b->y *= zoom;
a->z *= zoom;
b->z *= zoom;
a->x += WIN_WIDTH / 2;
b->x += WIN_WIDTH / 2;
a->y += WIN_HEIGHT / 2;
b->y += WIN_HEIGHT / 2;

void	ok()
{
	int	dx;
	int	dy;

	dx = b->x - a->x;
	dy = b->y - a->y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(dx, dy);
	else
		slope_bigger_than_one(dx, dy);
}

void	slope_bigger_than_one(int dx, int dy, t_point *a, t_point *b)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dx - dy;
	put_pixel(a->x, a->y);
	while (i < dy)
	{
		a->y += 1;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			a->x += 1;
			p = p + 2 * dx - 2 * dy;
		}
		put_pixel(a->x, a->y);
		i++;
	}
}

void	slope_less_then_one(int dx, int dy, t_point *a, t_point *b)
{
	int	p;
	int	i;

	i = -1;
	p = 2 * abs(dy) - abs(dx);
	while (++i < abs(dx))
	{
		if (dx > 0)
			a->x += 1;
		else
			a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				a->y += 1;
			else
				a->y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		put_pixel(a->x, a->y);
	}
}

void	draw_map()
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			draw_line(x, y, x + 1, y);
			draw_line(x, y, x, y + 1);
			y++;
		}
		x++;
	}
}

void	isometric(int x, int y, int z)
{
	int	tmp;

	tmp = x;
	x = (tmp - y) * cos(0.523599);
	y = (tmp + y) * sin(0.523599) - z;
}

float	function(x, y, t_point *a, t_point *b)
{
	int		dx;
	int		dy;
	float	fraction;

	dx = b->x - a->x;
	dy = b->y - a->y;
	if (abs(dx) > abs(dy))
		fraction = fraction(a->x, b->x, x);
	else
		fraction = fraction(a->y, b->y, y);
	return (fraction);
}

float	fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return ((x - x1) / (x2 - x1));
	return (0);
}
