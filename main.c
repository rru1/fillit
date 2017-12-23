/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 16:55:33 by ibondare          #+#    #+#             */
/*   Updated: 2017/12/23 18:52:55 by ibondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

int err(char *s)
{
	ft_putendl(s);
	return (1);
}

int	main(int ac, char **av)
{
	t_list	*list;
	t_map	*map;

	if (ac != 2)
		return(err("usage: ./fillit source_file"));
	if ((list = read_tt(open(av[1], O_RDONLY))) == NULL)
		return(err("error"));
	map = solve(list);
	print_map(map);
	free_map(map);
	free_list(list);
	return (0);
}
