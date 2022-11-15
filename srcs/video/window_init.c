#include "../../inc/cub3d.h"

void	init_graphics(t_game *game)
{
	t_img			*img;
	t_window		*window;

	img = malloc(sizeof(t_img));
	if (!img)
		exit_n_display("malloc failed\n");
	window = malloc(sizeof(t_window));
	if (!window)
		exit_n_display("malloc failed\n");
	game->img = img;
	game->img->img = NULL;
	game->win = window;
}

void	window_init(t_game *game)
{
	init_graphics(game);
	game->win->mlx_win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3d");
	game->win->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->win->img.addr = mlx_get_data_addr(game->win->img.img,
			&game->win->img.bpp, &game->win->img.linelen,
			&game->win->img.endian);
}
