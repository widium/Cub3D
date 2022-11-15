#include "../../inc/cub3d.h"

void	create_image(t_game *game)
{
	if (game->img->img != NULL)
		mlx_destroy_image(game->mlx, game->img->img);
	game->img->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img->addr = mlx_get_data_addr(game->img->img,
			&game->img->bpp, &game->img->linelen, &game->img->endian);
}

int	engine(t_game *game)
{
	create_image(game);
	draw_background(game);
	player_move(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win->mlx_win,
		game->img->img, 0, 0);
	mlx_do_sync(game->mlx);
	return (0);
}
