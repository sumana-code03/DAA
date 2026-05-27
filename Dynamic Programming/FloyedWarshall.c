#include <stdio.h>
#define INF 99999
#define MAX 10
void printMatrix(int matrix[MAX][MAX], int n, char name[])
{
    printf("\nMatrix %s:\n", name);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(matrix[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}
void printPath(int parent[MAX][MAX], int i, int j)
{
    if(i == j)
    {
        printf("%d", i + 1);
    }
    else if(parent[i][j] == -1)
    {
        printf("No path");
    }
    else
    {
        printPath(parent, i, parent[i][j]);
        printf(" -> %d", j + 1);
    }
}
void floydWarshall(int dist[MAX][MAX], int n)
{
    int i, j, k;
    int parent[MAX][MAX];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j || dist[i][j] == INF)
                parent[i][j] = -1;
            else
                parent[i][j] = i;
        }
    }
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
        char stepName[5];
        sprintf(stepName, "A^%d", k + 1);
        printMatrix(dist, n, stepName);
    }
    printf("\nFinal Paths and Weights:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i != j && dist[i][j] != INF)
            {
                printPath(parent, i, j);
                printf(" : %d\n", dist[i][j]);
            }
        }
    }
}
int main()
{
    int n, dist[MAX][MAX];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix (use 99999 for Infinity):\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &dist[i][j]);
        }
    }
    floydWarshall(dist, n);
    return 0;
}
