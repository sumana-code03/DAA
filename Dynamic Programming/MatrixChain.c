#include <stdio.h>
#include <limits.h>
int m[20][20];
int s[20][20];
void print_optimal_output(int s[20][20], int i, int j)
{
    if(i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        print_optimal_output(s, i, s[i][j]);
        print_optimal_output(s, s[i][j] + 1, j);
        printf(")");
    }
}
void matrix_chain_order(int p[], int n)
{
    int i, j, k, L, q;
    for(i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }
    for(L = 2; L <= n; L++)
    {
        for(i = 1; i <= n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    printf("\nMinimum Multiplication Costs\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (i > j) printf("\t");
            else printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\nOptimal Split Points 'k'\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (i >= j) printf("\t");
            else printf("%d\t", s[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int n, i;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    int p[n + 1];
    printf("Enter the dimensions ( %d values ): \n", n + 1);
    for (i = 0; i <= n; i++)
    {
        printf("p[%d]: ", i);
        scanf("%d", &p[i]);
    }
    matrix_chain_order(p, n);
    printf("\nMinimum number of scalar multiplications: %d\n", m[1][n]);
    printf("Optimal Parenthesization is: ");
    print_optimal_output(s, 1, n);
    printf("\n");
    return 0;
}
