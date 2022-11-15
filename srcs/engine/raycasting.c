#include "../../inc/cub3d.h"

void	digital_differential_analyzer(t_game *game)
{
	game->map_pos_x = game->rays.hit_x / (int)TILE;
	game->map_pos_y = game->rays.hit_y / (int)TILE;
	while (game->map_pos_x > 0 && game->map_pos_x < game->map_w
		&& game->map_pos_y > 0 && game->map_pos_y < game->map_h
		&& game->map[game->map_pos_y][game->map_pos_x] != '1')
	{
		game->rays.hit_x += game->rays.step_x;
		game->rays.hit_y += game->rays.step_y;
		game->map_pos_x = game->rays.hit_x / (int)TILE;
		game->map_pos_y = game->rays.hit_y / (int)TILE;
	}
}

double	vertical_raycasting(t_game *game)
{
	game->rays.tan = tan(deg_to_rad(game->rays.ang));
	if (game->rays.ang < NORTH || game->rays.ang > SOUTH)
	{
		game->rays.step_x = TILE;
		game->rays.hit_x = floor(game->p.x / TILE) * TILE + TILE;
	}
	else
	{
		game->rays.step_x = -TILE;
		game->rays.hit_x = floor(game->p.x / TILE) * TILE - 0.00001;
	}
	game->rays.hit_y = game->p.y
		+ (game->p.x - game->rays.hit_x) * game->rays.tan;
	if (game->rays.ang == WEST || game->rays.ang == EAST)
		game->rays.step_y = 0;
	else
		game->rays.step_y = TILE * (game->rays.tan * -1);
	if (game->rays.ang >= NORTH && game->rays.ang <= SOUTH)
		game->rays.step_y *= -1;
	digital_differential_analyzer(game);
	return (sqrt(square((game->p.x - game->rays.hit_x))
			+ square((game->p.y - game->rays.hit_y))));
}

double	horizontal_raycasting(t_game *game)
{
	game->rays.tan = tan(deg_to_rad(game->rays.ang));
	if (game->rays.ang > EAST && game->rays.ang < WEST)
	{
		game->rays.step_y = -TILE;
		game->rays.hit_y = floor(game->p.y / TILE) * TILE - 0.00001;
	}
	else
	{
		game->rays.step_y = TILE;
		game->rays.hit_y = floor(game->p.y / TILE) * TILE + TILE;
	}
	game->rays.hit_x = game->p.x
		+ (game->p.y - game->rays.hit_y) / game->rays.tan;
	if (game->rays.ang == NORTH || game->rays.ang == SOUTH)
		game->rays.step_x = 0;
	else
		game->rays.step_x = TILE / game->rays.tan;
	if (game->rays.ang > WEST)
		game->rays.step_x *= -1;
	digital_differential_analyzer(game);
	return (sqrt(square((game->p.x - game->rays.hit_x))
			+ square((game->p.y - game->rays.hit_y))));
}

void	raycasting(t_game *game)
{
	game->column = 0;
	game->rays.ang = game->p.vis + FOV / 2;
	while (game->column < WIN_W)
	{
		game->flag_hori = 0;
		game->flag_exit = 0;
		while (game->rays.ang >= 360)
			game->rays.ang -= 360;
		while (game->rays.ang < 0)
			game->rays.ang += 360;
		game->h_res = horizontal_raycasting(game);
		game->rays.h_hit_x = game->rays.hit_x;
		game->v_res = vertical_raycasting(game);
		game->rays.v_hit_y = game->rays.hit_y;
		if (game->h_res < game->v_res)
		{
			game->flag_hori = 1;
			game->rays.dist = game->h_res;
		}
		else
			game->rays.dist = game->v_res;
		draw(game);
		game->rays.ang -= FOV / (double)WIN_W;
		game->column++;
	}
}
