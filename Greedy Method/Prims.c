#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
int minkey(int n, int key[], bool mstset[])
{
    int minvalue = INT_MAX;
    int minind = -1;
    for(int i = 0; i < n; i++)
    {
        if(mstset[i] == false && key[i] < minvalue)
        {
            minvalue = key[i];
            minind = i;
        }
    }
    return minind;
}
void prims(int n, int adj[n][n], char start)
{
    int key[n];
    int parent[n];
    bool mstset[n];
    int order[n];
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        key[i] = INT_MAX;
        mstset[i] = false;
        parent[i] = -1;
    }
    int startind = start - 'A';
    key[startind] = 0;
    for(int count = 0; count < n; count++)
    {
        int u = minkey(n, key, mstset);
        mstset[u] = true;
        order[k++] = u;
        for(int i = 0; i < n; i++)
        {
            if(adj[u][i] != 0 && mstset[i] == false && adj[u][i] < key[i])
            {
                parent[i] = u;
                key[i] = adj[u][i];
            }
        }
        printf("Iteration %d:\n", count + 1);
        printf("Selected Vertex: %c\n", u + 'A');
        printf("Key array: ");
        for(int i = 0; i < n; i++)
        {
            if(key[i] == INT_MAX)
                printf("INF ");
            else
                printf("%d ", key[i]);
        }
        printf("\nMST Set: ");
        for(int i = 0; i < n; i++)
        {
            printf("%d ", mstset[i]);
        }
        printf("\n\n");
    }
    int total = 0;
    printf("Edges in MST:\n");
    printf("%c\n", start);
    for(int i = 1; i < n; i++)
    {
        int v = order[i];
        printf("%c - %c \t Weight = %d\n",
        parent[v] + 'A',
        v + 'A',
        adj[v][parent[v]]);
        total += adj[v][parent[v]];
    }
    printf("Total Weight = %d\n", total);
}
int main()
{
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int adj[n][n];
    printf("Enter adjacency matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }
    char start;
    printf("Enter starting vertex (A, B, C...): ");
    scanf(" %c", &start);
    prims(n, adj, start);
    return 0;
}
