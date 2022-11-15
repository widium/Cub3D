#include "../../inc/cub3d.h"

int	check_all_datas(t_game *game)
{
	if (game->text.no.path
		&& game->text.so.path
		&& game->text.we.path
		&& game->text.ea.path
		&& game->text.ceiling.path
		&& game->text.floor.path)
		return (1);
	return (0);
}

int	first_wall_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] == '\0')
		return (0);
	skip_white_space(line, &i);
	while (line[i] == WALL)
	{
		i++;
		skip_white_space(line, &i);
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	collect_data(char *l, t_game *game)
{
	if (!l)
		return (0);
	if (!ft_strncmp(l, "NO", 2) && game->text.no.path == NULL)
		game->text.no.path = ft_strtrim(l + 2, " \t\r\n");
	else if (!ft_strncmp(l, "SO", 2) && game->text.so.path == NULL)
		game->text.so.path = ft_strtrim(l + 2, " \t\r\n");
	else if (!ft_strncmp(l, "EA", 2) && game->text.ea.path == NULL)
		game->text.ea.path = ft_strtrim(l + 2, " \t\r\n");
	else if (!ft_strncmp(l, "WE", 2) && game->text.we.path == NULL)
		game->text.we.path = ft_strtrim(l + 2, " \t\r\n");
	else if (!ft_strncmp(l, "C", 1) && game->text.ceiling.path == NULL)
		game->text.ceiling.path = ft_strtrim(l + 1, " \t\r\n");
	else if (!ft_strncmp(l, "F", 1) && game->text.floor.path == NULL)
		game->text.floor.path = ft_strtrim(l + 1, " \t\r\n");
	else
		return (0);
	return (1);
}

int	game_infos(t_game *game, t_parse *control)
{
	char	*line;

	line = get_next_line(control->fd);
	while (line)
	{
		while (line[0] == '\0' || line_only_w_spaces(line) == 0)
		{
			free(line);
			line = get_next_line(control->fd);
		}
		if (first_wall_line(line))
			break ;
		if (!collect_data(line, game))
			return (0);
		free(line);
		line = get_next_line(control->fd);
	}
	if (!check_all_datas(game))
		return (0);
	game->map = collect_map(line, control->fd);
	if (!game->map)
		return (0);
	return (1);
}
