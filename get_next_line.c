#include "get_next_line.h"

static int		ft_read_file(char **str, int fd)
{
	int		ret;
	char	*s;
	char	buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[ret] = '\0';
	s = *str;
	*str = ft_strjoin(*str, buf);
	if (*s != 0)
		free(s);
	return (ret);
}

static int		ft_get_line(char **str, char **line, char *s)
{
	int		l;;
	char	*joinstr;

	l = 0;
	if (*s == '\n')
		l = 1;
	*s = 0;
	*line = ft_strjoin("", *str);
	if (l == 0 && ft_strlen(*str) != 0)
	{
		*str = ft_strnew(1);
		return (1);
	}
	else if (l == 0 && !(ft_strlen(*str)))
		return (0);
	joinstr = *str;
	*str = ft_strjoin(s + 1, "");
	free(joinstr);
	return (l);
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	char		*s;
	static char	*str;

	if (!line || BUFF_SIZE < 1)
		return (-1);
	if (str == 0)
		str = "";
	ret = BUFF_SIZE;
	while (line)
	{
		s = str;
		while (*s || ret < BUFF_SIZE)
		{
			if (*s == '\n' || *s == 0 || *s == -1)
				return (ft_get_line(&str, line, s));
			s++;
		}
		ret = ft_read_file(&str, fd);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
