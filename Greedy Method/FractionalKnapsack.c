#include <stdio.h>
void calculate(int n, float w[], float p[], float m, char* strategy)
{
    float x[20] = {0}, total_p = 0, remaining = m;
    int i;
    for (i = 0; i < n; i++)
    {
        if (w[i] <= remaining)
        {
            x[i] = 1.0;
            total_p += p[i];
            remaining -= w[i];
        }
        else
        {
            x[i] = remaining / w[i];
            total_p += (x[i] * p[i]);
            remaining = 0;
            break;
        }
    }
    printf("\nStrategy: %s", strategy);
    printf("\nSolution vector x: ");
    for (i = 0; i < n; i++) printf("%.2f  ", x[i]);
    printf("\nTotal Profit: %.2f\n", total_p);
    printf("---------------------------------");
}
void sortByRatio(int n, float w[], float p[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((p[i] / w[i]) < (p[j] / w[j]))
            {
                float temp = p[i]; p[i] = p[j]; p[j] = temp;
                temp = w[i]; w[i] = w[j]; w[j] = temp;
            }
        }
    }
}
void sortByMaxProfit(int n, float w[], float p[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i] < p[j])
            {
                float temp = p[i]; p[i] = p[j]; p[j] = temp;
                temp = w[i]; w[i] = w[j]; w[j] = temp;
            }
        }
    }
}
void sortByMinWeight(int n, float w[], float p[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (w[i] > w[j])
            {
                float temp = w[i]; w[i] = w[j]; w[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }
}
int main()
{
    int n;
    float w[20], p[20], m, w_copy[20], p_copy[20];
    printf("Enter number of objects: ");
    scanf("%d", &n);
    printf("Enter weights: ");
    for (int i = 0; i < n; i++) scanf("%f", &w[i]);
    printf("Enter profits: ");
    for (int i = 0; i < n; i++) scanf("%f", &p[i]);
    printf("Enter knapsack capacity: ");
    scanf("%f", &m);
    for(int i=0; i<n; i++)
    {
        w_copy[i]=w[i];
        p_copy[i]=p[i]; 
    }
    sortByMaxProfit(n, w_copy, p_copy);
    calculate(n, w_copy, p_copy, m, "Maximum Profit");
    for(int i=0; i<n; i++)
    {
        w_copy[i]=w[i];
        p_copy[i]=p[i];
    }
    sortByMinWeight(n, w_copy, p_copy);
    calculate(n, w_copy, p_copy, m, "Minimum Weight");
    for(int i=0; i<n; i++)
    {
        w_copy[i]=w[i];
        p_copy[i]=p[i];
    }
    sortByRatio(n, w_copy, p_copy);
    calculate(n, w_copy, p_copy, m, "P/W Ratio (Greedy)");
    return 0;
}
