#include "get_next_line.h"

static int	index_new_line(char *buf);
static void	clear(char **keep);
static char	*return_readed_lines(char **keep, char **tmp, int readed);
static char	*read_file(char **keep, char **tmp, int *readed, int fd);

static int	index_new_line(char *buf)
{
	int	index;

	index = 0;
	while (*buf)
	{
		if (*buf == '\n')
			return (index);
		index++;
		buf++;
	}
	if (*buf == '\n')
		return (index);
	return (-1);
}

static char	*return_readed_lines(char **keep, char **tmp, int readed)
{
	int		index_nl;
	char	*ret;

	index_nl = index_new_line(*keep) + 1;
	if (index_nl > 0)
	{
		ret = ft_substr(*keep, 0, index_nl - 1);
		if (!ret)
			return (NULL);
		*tmp = ft_substr(*keep, index_nl, (ft_strlen(*keep) - index_nl));
		if (!tmp)
			return (NULL);
		free(*keep);
		*keep = *tmp;
		return (ret);
	}
	else if (**keep && !readed)
	{
		ret = ft_substr(*keep, 0, ft_strlen(*keep));
		if (!ret)
			return (NULL);
		clear(keep);
		return (ret);
	}
	return (NULL);
}

static char	*read_file(char **keep, char **tmp, int *readed, int fd)
{
	char	buf[BUFFER_SIZE + 1];

	*readed = read(fd, buf, BUFFER_SIZE);
	if (*readed < 0)
		return (NULL);
	buf[*readed] = '\0';
	*tmp = ft_strjoin(*keep, buf);
	if (!tmp)
		return (NULL);
	free(*keep);
	*keep = *tmp;
	return ("mamalemusty");
}

static void	clear(char **keep)
{
	free(*keep);
	*keep = NULL;
}

char	*get_next_line(int fd)
{
	char			*buf;
	static char		*keep;
	char			*tmp;
	int				readed;

	if (read(fd, 0, 0))
		return (NULL);
	if (!keep)
		keep = ft_substr("", 0, 1);
	readed = 0;
	while (keep)
	{
		if (index_new_line(keep) == -1)
		{
			buf = read_file(&keep, &tmp, &readed, fd);
			if (buf == NULL)
				return (NULL);
		}
		if (index_new_line(keep) + 1 > 0 || (*keep && !readed))
			return (return_readed_lines(&keep, &tmp, readed));
		if (!*keep && !readed)
			clear(&keep);
	}
	return (NULL);
}
