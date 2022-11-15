#include "../inc/cub3d.h"

int	exit_game(t_game *game)
{
	destroy_struct(game, NULL);
	exit(0);
}

void	set_hooks(t_game *game)
{
	mlx_hook(game->win->mlx_win, 17, STRUCTURENOTIFYMASK, exit_game, game);
	mlx_hook(game->win->mlx_win, KEYPRESS, KEYPRESSMASK, pressed, &game->keys);
	mlx_hook(game->win->mlx_win, KEYRELEASE, KEYRELEASEMASK,
		released, &game->keys);
	mlx_loop_hook(game->mlx, engine, game);
	mlx_loop(game->mlx);
}

int	pressed(int keycode, t_keys *keys)
{
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == W)
		keys->movefor = 1;
	if (keycode == S)
		keys->moveback = 1;
	if (keycode == D)
		keys->moveright = 1;
	if (keycode == A)
		keys->moveleft = 1;
	if (keycode == LEFT)
		keys->turnright = 1;
	if (keycode == RIGHT)
		keys->turnleft = 1;
	return (0);
}

int	released(int keycode, t_keys *keys)
{
	if (keycode == W)
		keys->movefor = 0;
	if (keycode == S)
		keys->moveback = 0;
	if (keycode == D)
		keys->moveright = 0;
	if (keycode == A)
		keys->moveleft = 0;
	if (keycode == LEFT)
		keys->turnright = 0;
	if (keycode == RIGHT)
		keys->turnleft = 0;
	return (0);
}
