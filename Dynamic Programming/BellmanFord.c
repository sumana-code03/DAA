#include <stdio.h>
#include <stdlib.h>
#define INF 999
struct Edge {
    int src, dest, weight;
};
void printPath(int parent[], int j)
{
    if (parent[j] == -1)
    {
        printf("%d", j + 1);
        return;
    }
    printPath(parent, parent[j]);
    printf("->%d", j + 1);
}
void bellmanFord(int V, int E, struct Edge edges[], int src)
{
    int dist[V];
    int last_dist[V];
    int parent[V];
    int table[V - 1][V];
    for(int i = 0; i < V; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;
    for(int k = 1; k < V; k++)
    {
        for(int i = 0; i < V; i++)
        {
            last_dist[i] = dist[i];
        }
        for(int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if(last_dist[u] != INF && last_dist[u] + weight < dist[v])
            {
                dist[v] = last_dist[u] + weight;
                parent[v] = u;
            }
        }
        for(int i = 0; i < V; i++)
        {
            table[k - 1][i] = dist[i];
        }
    }
    printf("\nDistance Table (k = iterations):\n");
    printf("k   ");
    for(int i = 1; i <= V; i++)
        printf("1->%d  ", i);
    printf("\n--------------------------------------------\n");
    for (int k = 0; k < V - 1; k++)
    {
        printf("%d   ", k + 1);
        for (int i = 0; i < V; i++)
        {
            if(table[k][i] >= INF)
                printf("INF   ");
            else
                printf("%-6d", table[k][i]);
        }
        printf("\n");
    }
    printf("\nPath:\n");
    for(int i = 1; i < V; i++)
    {
        printPath(parent, i);
        printf(":%d\n", dist[i]);
    }
}
int main()
{
    int V, E, source;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    struct Edge edges[E];
    printf("Enter edges (source destination weight):\n");
    for(int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        edges[i].src--;
        edges[i].dest--;
    }
    printf("Enter source vertex: ");
    scanf("%d", &source);
    bellmanFord(V, E, edges, source - 1);
    return 0;
}
