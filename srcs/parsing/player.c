#include "../../inc/cub3d.h"

void	get_player_infos(t_game *game)
{
	if (game->p.vis == 'N')
		game->p.vis = NORTH;
	else if (game->p.vis == 'S')
		game->p.vis = SOUTH;
	else if (game->p.vis == 'E')
		game->p.vis = EAST;
	else if (game->p.vis == 'W')
		game->p.vis = WEST;
	game->p.next_x = game->p.x;
	game->p.next_y = game->p.y;
	game->p.height = WIN_H / 2;
}

int	find_player_pos(char **map, t_game *game, t_parse *control)
{
	int	y;
	int	x;

	y = 0;
	while (map[y][0] != '\0')
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'W' || map[y][x] == 'E')
			{
				game->p.x = x * TILE + (TILE / 2);
				game->p.y = y * TILE + (TILE / 2);
				game->p.vis = map[y][x];
				control->spawn++;
			}
			x++;
		}
		y++;
	}
	return (1);
}
