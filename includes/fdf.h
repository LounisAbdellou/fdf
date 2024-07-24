/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/07/24 17:39:46 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 1200
# define HEIGHT 700

typedef struct s_delta {
	int	x;
	int	y;
}	t_delta;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_map {
	int	width;
	int	height;
	int	**points_z;
}	t_map;

typedef struct s_env {
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*map;
}	t_env;

char	*get_next_line(int fd);
size_t	get_line_count(char *filename);
void	draw_map(t_env *env);

#endif
