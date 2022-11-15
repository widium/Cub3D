#include "../inc/cub3d.h"

void	exit_n_display(char *str)
{
	if (write (1, str, ft_strlen(str)) == -1)
		exit (-1);
	exit(0);
}

void	destroy_struct(t_game *game, char *str)
{
	free_map(game, game->map);
	free(game->text.no.path);
	free(game->text.so.path);
	free(game->text.ea.path);
	free(game->text.we.path);
	free(game->text.ceiling.path);
	free(game->text.floor.path);
	ft_bzero(&game->text.no, sizeof(t_texture));
	ft_bzero(&game->text.so, sizeof(t_texture));
	ft_bzero(&game->text.ea, sizeof(t_texture));
	ft_bzero(&game->text.we, sizeof(t_texture));
	ft_bzero(&game->text.floor, sizeof(t_texture));
	ft_bzero(&game->text.ceiling, sizeof(t_texture));
	ft_bzero(&game->keys, sizeof(t_keys));
	ft_bzero(&game->p, sizeof(t_player));
	ft_bzero(&game->rays, sizeof(t_player));
	if (str)
		if (write(1, str, ft_strlen(str)) == -1)
			return ;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		init_game(&game);
		if (!parsing(argv[1], &game))
			destroy_struct(&game, "Error\n");
		else
		{
			video_init(&game);
			window_init(&game);
			set_hooks(&game);
		}
	}
	else
		if (write(1, "Wrong arguments\n", 16) == -1)
			return (-1);
	return (0);
}
