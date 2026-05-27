#include <stdio.h>
#define MAX 20
int graph[MAX][MAX];
int vis[MAX];
int queue[MAX];
int front = -1, rear = -1;
void add(int x)
{
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = x;
}
int delete()
{
    if (front == -1 || front > rear)
        return 0;
    return queue[front++];
}
void bfs(int s, int n)
{
    int p, i;
    add(s);
    vis[s] = 1;
    p = delete();
    while (p != 0)
    {
        printf("%d ", p);
        for (i = 1; i <= n; i++)
        {
            if (graph[p][i] == 1 && vis[i] == 0)
            {
                add(i);
                vis[i] = 1;
            }
        }
        p = delete();
    }
}
int main()
{
    int n, i, j, s;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    printf("Enter starting node: ");
    scanf("%d", &s);
    for (i = 1; i <= n; i++)
    {
        vis[i] = 0;
    }
    printf("BFS Traversal: ");
    bfs(s, n);
    for (i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
        {
            bfs(i, n);
        }
    }
    return 0;
}
