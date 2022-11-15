#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	int		size_src;
	int		c;
	char	*ret;

	size_src = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (size_src + 1));
	if (ret == NULL)
		return (NULL);
	c = 0;
	while (s1[c])
	{
		ret[c] = s1[c];
		c++;
	}
	ret[c] = '\0';
	return (ret);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	count;

	count = 0;
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (count < len)
	{
		ret[count] = s[start + count];
		count++;
	}
	ret[count] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		size;
	int		i;
	int		j;

	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	dst = (char *)malloc(sizeof(char) * size);
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	j = 0;
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	return (dst);
}
