#include <stdio.h>
#include <stdbool.h>
int N, totalSolutions = 0;
void printSolution(int board[N][N], int count)
{
    printf("Solution %d:\n", count);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(board[i][j])
                printf(" Q%d ", i + 1);
            else
                printf(" .  ");
        }
        printf("\n");
    }
    printf("\n");
}
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    for(i = 0; i < col; i++)
        if(board[row][i])
            return false;
    for(i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if(board[i][j])
            return false;
    for(i = row, j = col; j >= 0 && i < N; i++, j--)
        if(board[i][j])
            return false;
    return true;
}
void countSolutions(int board[N][N], int col)
{
    if(col == N)
    {
        totalSolutions++;
        return;
    }
    for(int i = 0; i < N; i++)
    {
        if(isSafe(board, i, col))
        {
            board[i][col] = 1;
            countSolutions(board, col + 1);
            board[i][col] = 0;
        }
    }
}
void solveAndPrint(int board[N][N], int col, int *currentCount)
{
    if(col == N)
    {
        (*currentCount)++;
        printSolution(board, *currentCount);
        return;
    }
    for(int i = 0; i < N; i++)
    {
        if(isSafe(board, i, col))
        {
            board[i][col] = 1;
            solveAndPrint(board, col + 1, currentCount);
            board[i][col] = 0;
        }
    }
}
int main()
{
    printf("Enter no. of queens: ");
    if(scanf("%d", &N) != 1 || N <= 0)
    {
        printf("Please enter a valid positive integer.\n");
        return 1;
    }
    int board[N][N];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            board[i][j] = 0;
    countSolutions(board, 0);
    if(totalSolutions == 0)
    {
        printf("\nNo solutions exist for N = %d\n", N);
    }
    else
    {
        printf("\nTotal number of solutions found: %d\n", totalSolutions);
        printf("\n");
        int currentCount = 0;
        solveAndPrint(board, 0, &currentCount);
    }
    return 0;
}
