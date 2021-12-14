/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolveboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlopez-m <rlopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:19:42 by rlopez-m          #+#    #+#             */
/*   Updated: 2021/12/14 12:31:37 by rlopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Borra espacios en blanco de los argumentos recogidos por consola.
 * Recibe fuente y destino para retornar char *.
 *
 */
void	remove_spaces(int cleaned[], char *inputs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (inputs[i] != '\0')
	{
		if (inputs[i] != 32 && (inputs[i] >= '0' && inputs[i] <= '4'))
		{
			cleaned[j] = inputs[i] - '0';
			j++;
		}
		else if (inputs[i] != ' ' && (inputs[i] < '0' || inputs[i] > '4'))
		{
			//REVISAR CONDICION
			write(1, "No hay valores validos", 22);
			exit (1);
		}
		i++;
	}
	// Control de numero de inputs que pasan. Si menori a 16 ERROR
	if (i != 31)
	{
		write(1, "ERROR", 5);
		exit(1);
	}
}

/*
 * 
 * Recibe los valores y crea la matriz para poder rellenarla segun las condiciones
 *
 */

void	print_board(int **board)
{
	int	index_row;
	int	index_col;
	char	c;

	index_row = 0;
	while (index_row < 4)
	{
		index_col = 0;
		while (index_col < 4)
		{
			c = board[index_row][index_col] + '0';
			write(1, &c, 1);
			write(1, " ", 1);
			index_col++;
		}
		index_row++;
		write(1, "\n", 1);
	}
}

/*
 * Copiar matriz
 *
 */

int	**copy_matrix(int **board)
{
	int	**matrix_cp;
	int	i;
	int	j;

	matrix_cp = (int **)malloc(sizeof(int) * 4);
	if (matrix_cp == NULL)
		write(1, "ERROR", 1);
	i = 0;
	while (i < 4)
	{
		matrix_cp[i] = (int *) malloc(sizeof(int) * 4);
		i++;
	}
	// Si hay error al reservar memoria sale del programa
	if (board[0] == NULL)
	{
		write(1, "ERROR", 5);
		exit(1);
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix_cp[i][j] = board[i][j];
			j++;
		}
		i++;
	}
	return (matrix_cp);
}

/*
 * Validar la matriz
 *
 */

int	validate_matrix(int **board)
{
	int	i;
	int	solved;
	int	ok_counter;

	solved = 0;
	while (solved)
	{
		if (ok_counter == 1)
			solved = 1;
	}
	return (1);
}

/*
 * Rellena las filas del array principal
 *
 */
void	fill_rows(int **board, int rows[], int row)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		board[row][i] = rows[i];
		i++;
	}
}
/*
 * Copia master board para almacenar las matrices de posibilidades
 * y libera la anterior
 *
 */

int	****copy_master_matrix(int ****master_board, int rows, int cols)
{
	int	****master_matrix_cp;
	int	i;
	int	j;

	master_matrix_cp = malloc(rows * cols);
	i = 0;

	while (i < cols) 
	{
		master_matrix_cp[i] = malloc(cols);
		i++;
	}
	// Si hay error al reservar memoria sale del programa
	if (master_matrix_cp[0] == NULL)
	{
		write(1, "copy_master_matrix: ERROR", 25);
		exit(1);
	}
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			master_matrix_cp[i][j] = master_board[i][j];
			j++;
		}
		i++;
	}
	free(master_board);
	return (master_matrix_cp);
}

/*
 * Crea master matrix para almacenar las posibles matrices
 *
 */

int	****create_master_matrix(int **board)
{
	int	****master_matrix;

	master_matrix = (int ****)malloc(1 * sizeof(int **));
	master_matrix[0] = (int ***)malloc(1 * sizeof(int **));
	master_matrix[0][0] = &*board;
	return(master_matrix);
}

/*
 * Rellena las columnas del array principal
 *
 */
void	fill_columns(int **board, int columns[], int col)
{
	int i;

	i = 0;
	while(i < 4)
	{
		board[i][col] = columns[i];
		i++;
	}
}

/*
 * Comprobacion entre colup y coldown. Recibe arrays ordenados por handle_values()
 * y valida las combinaciones posibles.
 *
 */
void	check_rows(int rows[][4], int **board)
{
	int subindex;
	int *values;

	subindex = 0;
	while(subindex < 4)
	{
		if(rows[0][subindex] == 4 && rows[1][subindex] == 1)
		{
			int values[] = {1, 2, 3, 4};
			//fill_rows(board, values, subindex);
		}
		else if((rows[0][subindex] == 3 && rows[1][subindex] == 1)
			   		|| (rows[0][subindex] == 3 && rows[1][subindex] == 2))
		{
			int values[] = {1, 3, 4, 2};
			//fill_rows(board, values, subindex);
		}
		else if((rows[0][subindex] == 1 && rows[1][subindex] == 3)
			   		|| (rows[0][subindex] == 1 && rows[1][subindex] == 2)
					|| (rows[0][subindex] == 1 && rows[1][subindex] == 4))
		{
			int values[] = {4, 3, 2, 1};
			//fill_rows(board, values, subindex);
		}
		else if((rows[0][subindex] == 2 && rows[1][subindex] == 2)
				|| (rows[0][subindex] == 2 && rows[1][subindex] == 3)
				|| (rows[0][subindex] == 2 && rows[1][subindex] == 1))
		{	
			int values[] = {3, 4, 2, 1};
			///fill_rows(board, values, subindex);
		}
		else
		{
			printf("ERROR\n");
			exit (1);	
		}
		subindex++;
	}
}

/*
 * Comprobacion entre colup y coldown. Recibe arrays ordenados por handle_values()
 * y valida las combinaciones posibles.
 *
 */
void	check_cols(int columns[][4], int **board)
{
	int subindex;
	int matrix_counter_rows;
	int matrix_counter_cols;
	int max_counter_cols;
	int ****master_matrix_cols;


	master_matrix_cols = create_master_matrix(board);
	subindex = 0;
	max_counter_cols = 1;
	matrix_counter_rows = 1;
	matrix_counter_cols = 1;
	while(subindex < 4)
	{
		if(columns[0][subindex] == 4 && columns[1][subindex] == 1)
		{
			int values[] = {1, 2, 3, 4};	
			int posibles = 1;
			int i = 0;
			matrix_counter_cols = 1;
			while(i < posibles)
			{
				fill_columns(board, values, subindex);
				master_matrix_cols = copy_master_matrix(master_matrix_cols, matrix_counter_rows, max_counter_cols);
				matrix_counter_cols++;
				i++;
			}
			max_counter_cols = matrix_counter_cols - 1; 
			matrix_counter_rows++;
		}
		else if((columns[0][subindex] == 3 && columns[1][subindex] == 1)
			   		|| (columns[0][subindex] == 3 && columns[1][subindex] == 2))
		{
			int values3[6][4] ={{1, 3, 2, 4},
			   					{2, 1, 3, 4}, 
								{2, 3, 1, 4}, 
								{1, 3, 4, 2}, 
								{1, 2, 4, 3}, 
								{2, 3, 4, 1}};
			matrix_counter_cols = 1;
			fill_columns(board, values3[1], subindex);
			//master_matrix_cols = copy_master_matrix(master_matrix_cols, 3, 1);
			matrix_counter_rows++;
			matrix_counter_cols++;
		}
		else if((columns[0][subindex] == 1 && columns[1][subindex] == 3)
			   		|| (columns[0][subindex] == 1 && columns[1][subindex] == 2)
					|| (columns[0][subindex] == 1 && columns[1][subindex] == 4))
		{
			int values1[5][4] = {{4, 3, 2, 1},
							 	{4, 1, 2, 3},
							 	{4, 2, 3, 1},
							 	{4, 3, 1, 2},
							 	{4, 1, 3, 2}};
			fill_columns(board, values1[2], subindex);
		}
		else if((columns[0][subindex] == 2 && columns[1][subindex] == 2) 
					|| (columns[0][subindex] == 2 && columns[1][subindex] == 3) 
					|| (columns[0][subindex] == 2 && columns[1][subindex] == 1)) 
		{
			int values2[11][4] = {{3, 1, 2, 4},
									{3, 4, 2, 1},
									{3, 2, 1, 4},
									{1, 4, 2, 3},
									{2, 4, 1, 3},
									{2, 1, 4, 3},
									{3, 1, 4, 2},
									{3, 2, 4, 1},
									{3, 4, 1, 2},
									{1, 4, 3, 2},
									{2, 4, 3, 1}};
			fill_columns(board, values2[1], subindex);
		}
		else
		{
			printf("ERROR\n");
			exit (1);
		}
		subindex++;
	}
}

/*
 * Comprobacion de suma de pares por filas y columnas; si res > 5 error
 *
 */

void	check_sum(int values[][4])
{
	int i;

	i = 0;
	while (i < 4)
	{
		if ((values[0][i] - values[1][i]) > 5)
		{	
			write(1, "ERROR", 5);
			exit (1);
		}
		i++;
	}
}

/*
 * Organiza valores por colup/coldown y rowleft/rowrigh con el valor devuelto por
 * clean_spaces().
 *
 */
void	handle_values(int clean_inputs[], int columns[][4], int rows[][4])
{
	int index;
	int subindex;
	int total_inputs;

	total_inputs = 0;
	index = 0;
	// Bucle de inputs para recoger valores de entrada de up/down y left/right
	while(index < 2)
	{
		subindex = 0;
		while(subindex < 4)
		{
			columns[index][subindex] = clean_inputs[total_inputs];
			subindex++;
			total_inputs++;
		}
		index++;
	}
	index = 0;
	while(index < 2)
	{
		subindex = 0;
		while(subindex < 4)
		{
			rows[index][subindex] = clean_inputs[total_inputs];
			subindex++;
			total_inputs++;
		}
		index++;
	}
}

/*
 * Crea matriz en memoria
 *
 */
int	**create_matrix()
{
	int **board;
	int i;

	// Reservamos memoria para la matriz
	board = (int **) malloc(sizeof(int *) * 4);
	i = 0;
	while (i < 4)
	{
		board[i] = (int *) malloc(sizeof(int) * 4);
		i++;
	}
	// Si hay error al reservar memoria sale del programa
	if(board[0] == NULL)
	{
		write(1, "ERROR", 5);
		exit(1);
	}
	return (board);
}

/*
 * Funcion main, recoge valores de consola y los envia a handle_values()
 *
 *
 */
int	main(int argc, char *argv[])
{
	int clean_inputs[16];
	int columns[2][4];
	int rows[2][4];
	int **board;

	if(argc == 2)
	{
		remove_spaces(clean_inputs, argv[1]);
		handle_values(clean_inputs, columns, rows);
		check_sum(columns);
		check_sum(rows);
		board = create_matrix();
		check_cols(columns, board);
		check_rows(rows, board);
		validate_matrix(board);
		print_board(board);
	}
	else
	{
		write(1, "ERROR", 5);
		return (1);
	}
	
	return (0);
}
