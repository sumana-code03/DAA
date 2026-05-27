#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int V;
int counter = 0; 

void printSolution(int color[])
{
    printf("Solution %d:- \n", ++counter);
    for (int i = 0; i < V; i++)
    {
        printf(" Node %d -> color %d\n", i + 1, color[i]);
    }
    printf("\n");
}

bool isSafe(int v, bool **graph, int color[], int c)
{
    for (int i = 0; i < V; i++)
    {
        if (graph[v][i] && c == color[i])
        {
            return false;
        }
    }
    return true;
}

void graphColoringUtil(bool **graph, int m, int color[], int v)
{
    if (v == V)
    {
        printSolution(color);
        return; 
    }

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(v, graph, color, c))
        {
            color[v] = c;

            graphColoringUtil(graph, m, color, v + 1);

            color[v] = 0;
        }
    }
}

bool graphColoring(bool **graph, int m)
{
    int *color = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        color[i] = 0;
    }

    printf("\n--- Finding All Possible Solutions ---\n");
    graphColoringUtil(graph, m, color, 0);

    if (counter == 0)
    {
        printf("\nSolution does not exist\n");
        free(color);
        return false;
    }

    printf("Total distinct solutions found: %d\n", counter);

    free(color);
    return true;
}

int main()
{
    int m;

    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1) return 1;

    bool *graph = (bool *)malloc(V * sizeof(bool *));
    for (int i = 0; i < V; i++)
    {
        graph[i] = (bool *)malloc(V * sizeof(bool));
    }

    printf("Enter the adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int temp;
            if (scanf("%d", &temp) != 1) return 1;
            graph[i][j] = temp;
        }
    }

    printf("Enter the number of colors: ");
    if (scanf("%d", &m) != 1) return 1;

    graphColoring(graph, m);

    for (int i = 0; i < V; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
