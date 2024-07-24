/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/07/24 17:39:11 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <stdio.h>

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->points_z[i]);
		i++;
	}
	free(map->points_z);
	free(map);
}

int	destroy(t_env *env)
{
	if (env->map != NULL)
		free_map(env->map);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	free(env);
	exit(1);
}

int	handle_keydown(int keycode, t_env *env)
{
	if (keycode == 65307)
		return (destroy(env));
	return (0);
}

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int	*convert_points_z(char *line, t_env *env)
{
	size_t	i;
	char	**str_tab;
	int		*int_tab;

	i = 0;
	str_tab = ft_split(line, ' ');
	if (env->map->width == -1)
		env->map->width = ft_tablen(str_tab);
	int_tab = malloc(sizeof(int) * env->map->width);
	if (!int_tab)
		return (NULL);
	while (str_tab[i] != NULL)
	{
		int_tab[i] = ft_atoi(str_tab[i]);
		i++;
	}
	free_tab(str_tab);
	return (int_tab);
}

int	handle_file_parse(int fd, size_t line_count, t_env *env)
{
	size_t	i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	env->map->height = line_count;
	env->map->points_z = malloc(sizeof(int *) * env->map->height);
	while (line != NULL)
	{
		env->map->points_z[i] = convert_points_z(line, env);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (1);
}

t_map	*init_map()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = -1;
	map->height = -1;
	map->points_z = NULL;
	return (map);
}

t_env	*init_env(char *filename)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		exit(1);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, filename);
	// if (!env->win)
	// 	ft_return_error("error initializing window", 1);
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	// if (!env->img)
	// 	ft_return_error("error initializing image", 1);
	// env->data_addr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
	// 		&env->endian);
	env->map = init_map();
	if (!env->map)
		destroy(env);
	// env->camera = NULL;	
	return (env);
}

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2)
		return (1);
	env = init_env(av[1]);
	mlx_hook(env->win, 2, 1L<<0, handle_keydown, env);
	mlx_hook(env->win, 17, 1L<<0, destroy, env);
	if (!handle_file_parse(open(av[1], O_RDONLY), get_line_count(av[1]), env))
		return (1);
	for (int i = 0; i < env->map->height; i++)
	{
		for (int j = 0; j < env->map->width; j++)
			printf("%d ", env->map->points_z[i][j]);
		printf("\n");
	}
	draw_map(env);
	mlx_loop(env->mlx);
	return (0);
}
