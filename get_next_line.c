#include "get_next_line.h"

static	int	ft_read_buffer(char **buffer, int fd)
{
	char	*str;
	char	buf[BUFF_SIZE + 1];
	int		ret;

	if ((ret = read(fd,buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[ret] = '\0';
	str = *buffer;
	*buffer = ft_strjoin(*buffer, buf);
	if (*str != 0)
		free(str);
	return (ret);
}

static	int	ft_get_line(char **buffer, char **line, char *str)
{
	char	*attach;
	int		i;

	i = 0;
	if (*str == '\n')
		i = 1;
	*str = 0;
	*line = ft_strjoin("", *buffer);
	if (i == 0 && ft_strlen(*buffer) != 0)
	{
		*buffer = ft_strnew(1);
		return (1);
	}
	else if (i == 0 && !(ft_strlen(*buffer)))
		return (0);
	attach = *buffer;
	*buffer = ft_strjoin(str + 1, "");
	free(attach);
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	static	char	*buffer;
	char			*str;
	int				ret;

	if (buffer == 0)
		buffer = "";
	if (!line || BUFF_SIZE < 1)
		return (-1);
	ret = BUFF_SIZE;
	while (line)
	{
		str = buffer;
		while (*str || ret < BUFF_SIZE)
		{
			if (*str == '\n' || *str == 0 || *str == -1)
				return (ft_get_line(&str, line, str));
			str++;
		}
		ret = ft_read_buffer(&buffer, fd);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
