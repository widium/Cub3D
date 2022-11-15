#include "../../inc/cub3d.h"

int	error_message(char *msg, int ret)
{
	if (write(1, msg, ft_strlen(msg)) == -1)
		return (-1);
	return (ret);
}

void	init_parse(t_parse *control)
{
	control->fd = 0;
	control->spawn = 0;
	control->wall_err = 0;
	control->path_err = 0;
	control->id_err = 0;
	control->rgb_err = 0;
}

int	check_data(t_texture_pack *pack, t_texture *texture, int count)
{
	char	**split;

	if (count > 1)
		return (1);
	split = ft_split(texture->path, ',');
	if (!split)
		return (0);
	if (split[2])
	{
		texture->r = ft_atoi(split[0]);
		texture->g = ft_atoi(split[1]);
		texture->b = ft_atoi(split[2]);
	}
	if (texture->r < 0 || texture->r > 255)
		return (0);
	if (texture->g < 0 || texture->g > 255)
		return (0);
	if (texture->b < 0 || texture->b > 255)
		return (0);
	free_array(split);
	return (check_data(pack, &pack->floor, ++count));
}

int	parsing(char *path, t_game *game)
{
	t_parse	control;

	init_parse(&control);
	if (!file_format(path, &control))
		return (error_message("File format error. Use .cub maps only\n", 0));
	if (!game_infos(game, &control))
		return (error_message("Check data format and try again\n", 0));
	if (!check_map(game->map, game, &control))
		return (error_message("Map error: make sure your map is valid\n", 0));
	if (!check_data(&game->text, &game->text.ceiling, 0))
		return (error_message("Data error: check format and try again\n", 0));
	if (!check_texture_format(game))
		return (error_message("Texture error: textures need .xpm format\n", 0));
	game->ratio = TILE * ((WIN_W / 2) / tan(deg_to_rad(FOV / 2)));
	return (1);
}
