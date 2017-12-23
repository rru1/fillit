/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:56:16 by ibondare          #+#    #+#             */
/*   Updated: 2017/12/23 23:02:00 by ibondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Лист, куда записываем саму детальку и значение
 * которым она будет печататься(A,B,C,D,...) */
typedef struct	s_list
{
	int		**tet;
	char	let;
	s_list	*next;
}				t_list;

/* Пороверят строку считанную с фйла длинной 21
 * Возвращает 1, если фигура правильная */
char		**check_nod(char *str)
{
	int nod;
	int i;
	char **s1;

	block = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				nod++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				nod++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				nod++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				nod++;
		}
		i++;
	}
	if (nod == 6 || nod == 8)
		s1 = ft_strsplit(str, '\n');
	else
	{
		ft_putendl("error");
		exit(1);
	}
}

/* Основная функция для чтения
 * Принимает av[1], т.е. название файла и возвращает готовый лист */
t_list		*get_list_of_tetri(char *file_name)
{
	int		fd;
	char	buff[21];
	char	letter;
	t_list	*new;

	letter = 'A';
	ft_bzero(buff, 21);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putendl("error");
		exit(1);
	}
	new = read_file(fd, buff, letter);
	fd = close(fd);
	return (new);
}

/* Продолжение get_list_of_tetri */
static t_list	*read_file(int fd, char *buff, char letter)
{
	int			**tetri;
	t_list		*new;
	int			ret;
	int			flag;

	flag = 0;
	while ((ret = read(fd, buff, 21)) != 0)
	{
		if (flag == 1 || !(ft_isalpha(letter)))
		{
			ft_putendl("error");
			exit(1);
		}
		flag = ft_strlen(buff) == 20 ? flag + 1 : flag;
		tetri = valid(buff);
		ft_bzero(buff, 21);
		if (letter == 'A')
			new = ft_nlstnew(tetri, letter);
		else
			ft_nlstadd(new, tetri);
		letter++;
	}
	if (flag == 0)
	{
		ft_putendl("error");
		exit(1);
	}
	return (new);
}

/* Новый лист для тетри */ 
t_list		*ft_nlstnew(int **tet, char let)
{
	t_list	*nl;

	nl = (t_list *)malloc(sizeof(t_list));
	if (nl)
	{
		nl->tet = tet;
		nl->let = let;
		nl->next = NULL;
		return (nl);
	}
	else
		return (NULL);
}

/* Добавляет новое звено списка */
void		ft_nlstadd(t_list *nlst, int **tet)
{
	while (nlst->next)
		nlst = nlst->next;
	nlst->next = ft_nlstnew(tet, (nlst->letter + 1));
}

static void		map_valid(char *s)
{
	int		i;
	int		n;
	int		sharp;
	int		dot;

	dot = 12;
	i = 0;
	sharp = 4;
	n = (ft_strlen(s) == 22 ? 5 : 4);
	while (s[i])
	{
		if (s[i] == '#')
			sharp--;
		if (s[i] == '.')
			dot--;
		if (s[i] == '\n')
			n--;
		i++;
	}
	if (n != 0 || sharp != 0 || dot != 0)
		error();
}

static void		valid_slesh_n(char *s)
{
	int		len;

	len = ft_strlen(s);
	if (len == 22 && s[4] == '\n' && s[9] == '\n' && s[14] == '\n'
			&& s[19] == '\n' && s[20] == '\n')
		return ;
	else if (len == 20 && s[4] == '\n' && s[9] == '\n' && s[14] == '\n'
			&& s[19] == '\n')
		return ;
	else
		error();
}

static int		**coordinate_x_y(char **s, int **array)
{
	int		y;
	int		x;
	int		i;

	i = 1;
	y = 0;
	while (y <= 3)
	{
		x = 0;
		while (s[y][x])
		{
			if (s[y][x] == '#')
			{
				array[i][0] = y;
				array[i][1] = x;
				i++;
			}
			x++;
		}
		y++;
	}
	return (array);
}

int				**valid(char *s)
{
	char	**s1;
	int		**array;
	int		i;

	i = 1;
	array = (int**)malloc(sizeof(int*) * 5);
	while (i <= 4)
	{
		array[i] = (int*)malloc(sizeof(int) * 3);
		i++;
	}
	map_valid(s);
	valid_slesh_n(s);
	s1 = check_nod(s);
	array = coordinate_x_y(s1, array);
	return (array);
}
