/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:13:04 by dchen             #+#    #+#             */
/*   Updated: 2019/06/11 16:48:46 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_connection(char *str, int b_read)
{
	int i;
	int connection;

	i = 0;
	connection = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (str[i + 1] == '#')
				connection++;
			if (str[i - 1] == '#')
				connection++;
			if (str[i - 5] == '#')
				connection++;
			if (str[i + 5] == '#')
				connection++;
		}
		i++;
	}
	return ((connection == 6 || connection == 8) ? 1 : 0);
}

/*
 *  checks if tetris is valid
*/
int		check_valid_tetris(char	*str, int b_read)
{
	int	i;
	int block;

	i = 0;
	block = 0;
	if (b_read < 20)
		return (0);
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (str[i] != '#' && str[i] != '.')
				return (0);
			if (str[i] == '#')
				block++;
			if (block > 4)
				return (0);
		}
		else if (str[i] != '\n')
			return (0);
		i++;
	}
	if (check_connection(str, b_read) == 0)
		return (0);
	if (b_read == 21 && str[20] != '\n' && block == 4)
		return (1);
	return (1);
}

/* gets coords for each blocks
 *
*/

piece	get_piece(char *str, char id)
{
	piece	s_piece;
	int		i;
	int		j;
	
	s_piece.blocks = (point *)malloc(sizeof(point) * 4);
	i = 0;
	j = 0;
	s_piece.id = id;
	/* s_piece.placed = 0; */
	while (i < 20)
	{
		if(str[i] == '#')/* removed the j == 0 */
		{
			s_piece.blocks[j].y = i / 5;
	/*		printf("(%d, ", s_piece.blocks[j].x); testing   */
			s_piece.blocks[j].x = i % 5;
	/*		printf("%d) ", s_piece.blocks[j].y);   */
			j++;
		}
		i++;
	}
	reset(&s_piece);
	return (s_piece);
}

piece	*read_file(const	int	fd, int	*num_pieces)
{
	char 	id;
	char	*buf;
	int		b_read;
	int 	i;
	piece	*pieceArr;

	pieceArr = (piece *)malloc(sizeof(piece) * 28);
	id = 'A';
	i = 0;
	buf = ft_strnew(21);
	while ((b_read = read(fd, buf, 21)) >= 20)
	{
		if (check_valid_tetris(buf, b_read) == 0)
			return (NULL);
		pieceArr[i] = get_piece(buf, id);
		i++;
		id++;
	}
	*num_pieces = id - 'A';
	return (pieceArr);
}
