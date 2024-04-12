#include <stdio.h>

#define SIZE		8

int g_qcount;
int g_count;
char g_board[SIZE][SIZE];

void init_board(void)
{
	int r, c;

	for (r = 0; r < SIZE; ++r)
		for (c = 0; c < SIZE; ++c)
			g_board[r][c] = '.';
}

void print_board(void)
{
	int r, c;

	printf("%d\n", g_count);

	for (r = 0; r < SIZE; ++r) {
		for (c = 0; c < SIZE; ++c)
			printf("%c", g_board[r][c]);
		printf("\n");
	}
	printf("\n");
}

void locate_queen(int row, int col)
{
	int r, c;

	g_board[row][col] = 'V';

	r = row;
	for (c = col + 1; c < SIZE; ++c)
		g_board[r][c] = 'o';
	for (c = col - 1; c >= 0; --c)
		g_board[r][c] = 'o';
	c = col;
	for (r = row - 1; r >= 0; --r)
		g_board[r][c] = 'o';
	for (r = row + 1; r < SIZE; ++r)
		g_board[r][c] = 'o';
	for (r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c)
		g_board[r][c] = 'o';
	for (r = row - 1, c = col + 1; r >= 0 && c < SIZE; --r, ++c)
		g_board[r][c] = 'o';
	for (r = row + 1, c = col - 1; r < SIZE && c >= 0; ++r, --c)
		g_board[r][c] = 'o';
	for (r = row + 1, c = col + 1; r < SIZE && c < SIZE; ++r, ++c)
		g_board[r][c] = 'o';
}

void queen8(int row, int col)
{
	char board[SIZE][SIZE];
	int r, c;

	for (; row < SIZE; ++row) {
		for (; col < SIZE; ++col) {
			if (g_board[row][col] == '.') {
				for (r = 0; r < SIZE; ++r) // copied the board and assigned it to a local variable so that original board is not changed.
					for (c = 0; c < SIZE; ++c)
						board[r][c] = g_board[r][c];

				++g_qcount;
				locate_queen(row, col);

				if (g_qcount == SIZE) {
					++g_count;
					print_board();
				}

				queen8(row, col);
				--g_qcount;

				for (r = 0; r < SIZE; ++r)
					for (c = 0; c < SIZE; ++c)
						g_board[r][c] = board[r][c];
			}
		}
		col = 0;
	}
}

int main(void)
{
	init_board();
	queen8(0, 0);

	return 0;
}
