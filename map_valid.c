/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:56:16 by ibondare          #+#    #+#             */
/*   Updated: 2017/12/09 18:29:24 by ibondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_tet
{
	int height;
	int wight;
	t_point p1;
	t_point p2;
	char	**piece;
}

t_list	read_tetri(int fd)
{
	char	*buff;
	int		actual;
	t_list	*list;

	buff = ft_strnew(21);
	if (actual = read(fd, buff, 21) <= 20)
		list = ft_lstnew(buff, actual);
	while (actual = read(fd, buff, 21) <= 20)
		if (check_nod(buff) == 1)
		{
			list->next = ft_lstnew(buff, actual);
			list = list->next;
		}
}

int		check_nod(char *str)
{
	int nod;
	int i;

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
	return (nod == 6 || nod == 8);
}
