#include <stdio.h>
#define MAX 20
int graph[MAX][MAX];
int vis[MAX];
int stack[MAX];
int top = -1;
void push(int x)
{
    if (top == MAX - 1)
        return;
    stack[++top] = x;
}
int pop()
{
    if (top == -1)
        return 0;
    return stack[top--];
}
void dfs_stack(int s, int n)
{
    int i, p;
    push(s);
    while (top != -1)
    {
        p = pop();
        if (vis[p] == 0)
        {
            vis[p] = 1;
            printf("%d ", p);
            for (i = n; i >= 1; i--)
            {
                if (graph[p][i] == 1 && vis[i] == 0)
                {
                    push(i);
                }
            }
        }
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
    printf("DFS Traversal: ");
    dfs_stack(s, n);
    for (i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
        {
            dfs_stack(i, n);
        }
    }
    return 0;
}
