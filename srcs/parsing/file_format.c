#include "../../inc/cub3d.h"

int	check_file_format(char *str, char *str2, int start)
{
	int	i;

	i = 0;
	while (str[start])
	{
		if (str[start] != str2[i])
			return (str[start] - str2[i]);
		else
		{
			start++;
			i++;
		}
	}
	return (0);
}

int	file_format(char *path, t_parse *control)
{
	int	size;

	size = ft_strlen(path);
	if (check_file_format(path, ".cub", size - 4))
		return (0);
	else
	{
		control->fd = open(path, O_RDONLY);
		if (control->fd < 0)
			return (0);
	}
	return (1);
}

int	check_texture_format(t_game *game)
{
	int	size;

	size = ft_strlen(game->text.no.path);
	if (check_file_format(game->text.no.path, ".xpm", size - 4))
		return (0);
	size = ft_strlen(game->text.so.path);
	if (check_file_format(game->text.so.path, ".xpm", size - 4))
		return (0);
	size = ft_strlen(game->text.ea.path);
	if (check_file_format(game->text.ea.path, ".xpm", size - 4))
		return (0);
	size = ft_strlen(game->text.we.path);
	if (check_file_format(game->text.we.path, ".xpm", size - 4))
		return (0);
	return (1);
}
