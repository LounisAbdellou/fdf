/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:03:59 by labdello          #+#    #+#             */
/*   Updated: 2024/07/22 17:26:18 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 1200
# define HEIGHT 700

typedef struct s_map {
	int	width;
	int	height;
	int	**points;
}	t_map;

typedef struct s_env {
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*map;
}	t_env;

char	*get_next_line(int fd);
size_t	get_line_count(char *filename);

#endif
