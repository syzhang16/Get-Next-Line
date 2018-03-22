#include "get_next_line.h"

//fonction qui va me permettre d'indiquer quel caractere je souhaite qu'il cherche
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

static char	*ft_join(char **line, char const *buff)
{
	char	*tmp;
	int		i;

	if ((i = ft_search_char(buff, '\n')) < -1) // on recupere l'index d'un \n dans le buffer
		return (NULL);
	i = (i == -1) ? ft_strlen(buff) : i; // si -1 c'est qu'il n'y a pas de \n
	if (!(tmp = ft_strnew(ft_strlen(*line) + (i)))) //on cree une nouvelle str avec la taille de *line et de i
		return (NULL);
	ft_strcpy(tmp, *line); //on fait un strjoin
	ft_strdel(&(*line));
	ft_strncat(tmp, (char*)buff, i);
	ft_strcpy((char*)buff, &(buff[(buff[i] == '\n') ? (i + 1) : i])); //on deplace l'index 0 du buffer apres le \n en faisant une copie
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static char		buff[BUFF_SIZE + 1];
	int				ret;
	int				endl;

	if (fd < 0 || !line || !(*line = ft_strnew(BUFF_SIZE)) || !BUFF_SIZE) //on check le necessaire
		return (-1);
	endl = -1; //si endl = -1 c'est qu'on a lu une ligne
	while (endl == -1)
	{
		if (!buff[0]) //si mon buffer est vide a l'index 0 on le remplis de 0
			ft_bzero(buff, BUFF_SIZE + 1);
		if (!buff[0] && (ret = read(fd, buff, BUFF_SIZE)) < 0) //si mon buffer est vide a l'index 0 on lit la ligne
			return (-1);
		if (!ret && **line) //ret = la valeur de retour de read si elle est egale a 0 et que **line est pas vide on dit que la ligne est lue
			return (1);
		if (!ret && !buff[0]) //si ret = 0 et que buff[0] == \0 alors on dit que le fichier est lu en entier
			return (0);
		if ((endl = ft_search_char(buff, '\n')) < -1 || //on check si on a des erreurs en lancant les fonctions
				!(*line = ft_join(line, buff)))
			return (-1);
	}
	return (1);
}
