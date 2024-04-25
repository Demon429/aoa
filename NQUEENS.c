#include <stdio.h>
#include <stdbool.h>

bool isSafe(int board[][10], int row, int col, int n) {
	int i, j;

	// Check this row on the left side
	for (i = 0; i < col; i++)
    	if (board[row][i])
        	return false;

	// Check upper diagonal on left side
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    	if (board[i][j])
        	return false;

	// Check lower diagonal on left side
	for (i = row, j = col; j >= 0 && i < n; i++, j--)
    	if (board[i][j])
        	return false;

	return true;
}

bool solveNQUtil(int board[][10], int col, int n) {
	if (col >= n)
    	return true;

	for (int i = 0; i < n; i++) {
    	if (isSafe(board, i, col, n)) {
        	board[i][col] = 1;
        	if (solveNQUtil(board, col + 1, n))
            	return true;
        	board[i][col] = 0; // Backtrack
    	}
	}

	return false;
}

bool solveNQ(int n) {
	int board[10][10] = {0};

	if (solveNQUtil(board, 0, n) == false) {
    	printf("Solution does not exist\n");
    	return false;
	}

	// Print the solution
	for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++)
        	printf("%d ", board[i][j]);
    	printf("\n");
	}

	return true;
}

int main() {
	int n;
	printf("Enter the number of queens: ");
	scanf("%d", &n);

	if (n <= 3 || n >= 10) {
    	printf("No solution exists for %d queens.\n", n);
    	return 0;
	}

	solveNQ(n);

	return 0;
}
