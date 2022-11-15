#include "../../inc/cub3d.h"

int	is_w_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	skip_white_space(char *str, int *i)
{
	if (!str)
		return ;
	while (is_w_space(str[*i]))
		*i += 1;
}

void	vertical_skip_white_space(char **str, int *i, int x)
{
	if (!str)
		return ;
	while (is_w_space(str[*i][x]) && str[*i][x])
		*i += 1;
}

void	free_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	if (!map || map[i])
		return ;
	while (map[i] && i < game->map_h)
		free(map[i++]);
	free(map);
}

void	dup_array(char **tab, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		tab[i] = ft_strdup(tmp[i]);
		if (!tab[i])
			exit_n_display("malloc failed\n");
		i++;
	}
	if (tmp)
		free_array(tmp);
}
