#include "../../inc/cub3d.h"

char	**alloc_n_fill_array(char **tab)
{
	char	**ret;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		exit_n_display("malloc failed\n");
	i = 0;
	while (tab[i])
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
			exit_n_display("malloc failed\n");
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	realloc_string(char **map, int row, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		exit_n_display("malloc failed\n");
	while (map[row][i])
	{
		tmp[i] = map[row][i];
		i++;
	}
	free(map[row]);
	while (i < len)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	map[row] = ft_strdup(tmp);
	if (!map[row])
		exit_n_display("malloc failed\n");
	free(tmp);
}

char	**format_map(char **map)
{
	int	max_x;
	int	max_y;
	int	i;
	int	len;

	max_x = 0;
	max_y = 0;
	if (!map)
		return (NULL);
	get_max(map, &max_y, &max_x);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_x)
			realloc_string(map, i, max_x);
		i++;
	}
	free(map[i]);
	map[i] = malloc(sizeof(char) * max_x + 1);
	if (!map[i])
		exit_n_display("malloc failed\n");
	while (max_x != -1)
		map[i][max_x--] = '\0';
	return (map);
}

int	init_collect(int *row, char ***tmp, char ***tab, char *line)
{
	*row = 0;
	*tmp = NULL;
	*tab = NULL;
	if (!line)
		return (0);
	return (1);
}

char	**collect_map(char *line, int fd)
{
	char	**tab;
	char	**tmp;
	int		row;

	if (!init_collect(&row, &tmp, &tab, line))
		return (NULL);
	while (line)
	{
		if (tab)
			tmp = alloc_n_fill_array(tab);
		if (tab)
			free_array(tab);
		tab = (char **)malloc(sizeof(char *) * (++row + 1));
		if (!tab)
			exit_n_display("malloc failed\n");
		if (tmp)
			dup_array(tab, tmp);
		tab[row - 1] = ft_strdup(line);
		if (!tab[row - 1])
			exit_n_display("malloc failed\n");
		tab[row] = 0;
		free(line);
		line = get_next_line(fd);
	}
	return (format_map(tab));
}
