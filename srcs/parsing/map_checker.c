#include "../../inc/cub3d.h"

int	control_axis_x(char **map, int y, int max_y)
{
	int	x;

	x = 0;
	if (y == max_y)
		return (1);
	if (map[y][x] != '\0')
	{
		skip_white_space(map[y], &x);
		while (map[y][x] == WALL && map[y][x] != '\0')
		{
			while (map[y][x] != '\0' && !is_w_space(map[y][x]))
				x++;
			if (map[y][x - 1] != WALL)
				return (0);
			skip_white_space(map[y], &x);
		}
		if (map[y][x] == '\0')
			return (control_axis_x(map, y + 1, max_y));
		else
			return (0);
	}
	return (0);
}

int	control_axis_y(char **map, int x, int max_x)
{
	int	y;

	y = 0;
	if (x == max_x)
		return (1);
	if (map[y][x] != '\0')
	{
		vertical_skip_white_space(map, &y, x);
		while (map[y][x] == WALL)
		{
			while (map[y][x] != '\0' && !is_w_space(map[y][x]))
				y++;
			if (map[y - 1][x] != WALL)
				return (0);
			vertical_skip_white_space(map, &y, x);
		}
		if (map[y][x] == '\0')
			return (control_axis_y(map, x + 1, max_x));
		else
			return (0);
	}
	return (0);
}

void	get_max(char **map, int *max_y, int *max_x)
{
	int	i;
	int	greater_value;

	i = 0;
	greater_value = 0;
	while (map[*max_y] && map[*max_y][0] != '\0')
		*max_y += 1;
	while (i != *max_y)
	{
		while (map[i][*max_x])
			*max_x += 1;
		if (*max_x > greater_value)
			greater_value = *max_x;
		i++;
		*max_x = 0;
	}
	*max_x = greater_value;
}

int	check_map(char **map, t_game *game, t_parse *control)
{
	int	max_y;
	int	max_x;

	max_y = 0;
	max_x = 0;
	get_max(map, &max_y, &max_x);
	game->map_w = max_x;
	game->map_h = max_y;
	if (!control_axis_x(map, 0, max_y))
		return (0);
	if (!control_axis_y(map, 0, max_x))
		return (0);
	if (!find_player_pos(map, game, control) || control->spawn != 1)
		return (0);
	get_player_infos(game);
	return (1);
}

int	line_only_w_spaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (is_w_space(line[i]) == 0)
			return (1);
	return (0);
}
