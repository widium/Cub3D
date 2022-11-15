#include "../../inc/cub3d.h"

unsigned int	get_pixel(t_texture tex, int x, int y)
{
	char	*dst;

	dst = tex.img.addr + (y * tex.img.linelen + x * (tex.img.bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_background(t_game *game)
{
	int				x;
	int				y;
	t_texture		color;

	y = -1;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	define_color(&color, &game->text.ceiling);
	while (++y < WIN_H)
	{
		x = -1;
		if (y == WIN_H / 2)
			define_color(&color, &game->text.floor);
		while (++x < WIN_W)
			put_pixel(game->img, x, y, color_picker(color.r, color.g, color.b));
	}
}

void	draw_wall(t_game *game)
{
	if (game->text.wall.path == game->text.so.path
		|| game->text.wall.path == game->text.we.path)
		game->rays.text_x = WALL_RES - game->rays.text_x;
	while (game->start < game->end)
	{
		game->rays.text_y = WALL_RES / game->rays.length
			* (game->start - game->p.height + game->rays.length / 2);
		game->color = get_pixel(game->text.wall,
				game->rays.text_x, game->rays.text_y);
		put_pixel(game->img, game->column, game->start, game->color);
		game->start++;
	}
}

void	draw(t_game *game)
{
	game->rays.dist *= cos(deg_to_rad(game->p.vis - game->rays.ang));
	game->rays.length = game->ratio / game->rays.dist;
	game->start = game->p.height - game->rays.length / 2 + 1;
	game->end = game->p.height + game->rays.length / 2;
	if (game->start < 0)
		game->start = 0;
	if (game->end >= WIN_H)
		game->end = WIN_H - 1;
	if (game->flag_hori)
	{
		game->rays.text_x = fmod(game->rays.h_hit_x, TILE);
		if (game->rays.ang > EAST && game->rays.ang < WEST)
			game->text.wall = game->text.so;
		else
			game->text.wall = game->text.no;
	}
	else
	{
		game->rays.text_x = fmod(game->rays.v_hit_y, TILE);
		if (game->rays.ang >= NORTH && game->rays.ang <= SOUTH)
			game->text.wall = game->text.ea;
		else
			game->text.wall = game->text.we;
	}
	draw_wall(game);
}
