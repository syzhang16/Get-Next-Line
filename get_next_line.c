#include "get_next_line.h"

static int		ft_search_char(char const *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (-2);
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

static char	*gnl_join(char **line, char const *buff)
{
	char	*tmp;
	int		n;

	if ((n = ft_strindexchr(buff, '\n')) < -1)
		return (NULL);
	n = (n == -1) ? ft_strlen(buff) : n;
	if (!(tmp = ft_strnew(ft_strlen(*line) + (n))))
		return (NULL);
	ft_strcpy(tmp, *line);
	ft_strdel(&(*line));
	ft_strncat(tmp, (char*)buff, n);
	ft_strcpy((char*)buff, &(buff[(buff[n] == '\n') ? (n + 1) : n]));
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static char		buff[BUFF_SIZE + 1];
	int				ret;
	int				endl;

	if (fd < 0 || !line || !(*line = ft_strnew(BUFF_SIZE)) || !BUFF_SIZE)
		return (-1);
	endl = -1;
	while (endl == -1)
	{
		if (!buff[0])
			ft_bzero(buff, BUFF_SIZE + 1);
		if (!buff[0] && (ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (!ret && **line)
			return (1);
		if (!ret && !buff[0])
			return (0);
		if ((endl = ft_strindexchr(buff, '\n')) < -1 ||
				!(*line = gnl_join(line, buff)))
			return (-1);
	}
	return (1);
}
