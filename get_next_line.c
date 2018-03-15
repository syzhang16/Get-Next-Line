#include "get_next_line.h"

/*static char		*ft_join(char *s1, const char *s2)
{
	char	*tmp;

	if (!(tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(tmp, s1);
	free(s1);
	ft_strcat(tmp, s2);
	return (tmp);
}*/

static	char	*ft_join(char const *s1, char const *s2)
{
	char	*tmp;

	if ((tmp = ft_strnew((size_t)ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (tmp);
	ft_strcpy(tmp, s1);
	ft_strcat(tmp, s2);
	return (tmp);
}

static	int		ft_read_file(char **str, int fd)
{
	int		ret;
	char	*s;
	char	buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[ret] = '\0';
	s = *str;
	*str = ft_join(*str, buf);
	if (*s != 0)
		free(s);
	return (ret);
}

static	int		ft_gl(char **str, char **line, char *s)
{
	int		lines;;
	char	*joinstr;

	lines = 0;
	if (*s == '\n')
		lines = 1;
	*s = '\0';
	*line = ft_join("", *str);
	if (lines == 0 && ft_strlen(*str) != 0)
	{
		*str = ft_strnew(1);
		return (1);
	}
	else if (lines == 0 && !(ft_strlen(*str)))
		return (0);
	joinstr = *str;
	*str = ft_join(s + 1, "");
	free(joinstr);
	return (lines);
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	char		*s;
	static char	*str;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (str == '\0')
		str = "";
	ret = BUFF_SIZE;
	while (line)
	{
		s = str;
		while (*s || ret < BUFF_SIZE)
		{
			if (*s == '\n' ||*s == '\0' || *s == -1)
				return (ft_gl(&str, line, s));
			s++;
		}
		ret = ft_read_file(&str, fd);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
