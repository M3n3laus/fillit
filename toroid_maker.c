#include "fillit.h"


column_o	*init_toroid(piece *arr, int num, int board_size)
{
	column_o	*master_co;
	int			i;

	i = 0;
	master_co = make_columns_part_one(arr, num, board_size);
	link_list_header(master_co);
	while (i < num)
	{
		make_rows(arr[i], board_size, master_co);
		++i;
	}
	return(master_co);
}

void		make_rows(piece pc, int board_size, column_o *master_co)
{
	int n;
	int y;
	int i;

	y = 0;
	while((n = valid(pc, board_size)) != 2)
	{
		if (n == 0)
		{
			cell_linker(master_co, generate_rows(), pc);
			move_piece(&pc, 0);
		}
		if (n == 1)
		{
			i = 0;
			++y;
			reset(&pc);
			while (i < y)
			{
				move_piece(&pc, 1);
				i++;
			}
		}
	}
}

int			valid(piece pc, int board_size)
{
	int j;

	j = 0;
	while (j < 4)
	{
		if (pc.blocks[j].x >= board_size)
			return (1);
		if (pc.blocks[j].y >= board_size)
			return (2);
		++j;
	}
	return (0);
}
	