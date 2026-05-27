#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
#define INF 100000
int target[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};
struct Node {
    struct Node* parent;
    int matrix[N][N];
    int x, y;
    int cost;
    int level;
};
void displayTable(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
struct Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, struct Node* parent) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->parent = parent;
    memcpy(node->matrix, mat, sizeof(node->matrix));
    int temp = node->matrix[x][y];
    node->matrix[x][y] = node->matrix[newX][newY];
    node->matrix[newX][newY] = temp;
    node->cost = INF;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}
int calculateCost(int mat[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] && mat[i][j] != target[i][j]) {
                count++;
            }
        }
    }
    return count;
}
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}
void printPath(struct Node* root, int* step) {
    if (root == NULL)
        return;
    printPath(root->parent, step);
    if (*step == 0) {
        printf("Initial State:\n");
    } else {
        printf("Step %d:\n", *step);
    }
    displayTable(root->matrix);
    (*step)++;
}
void moveRight(int mat[N][N], int* nextX, int* nextY, int currentX, int currentY) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == currentX && j == currentY) {
                if (isSafe(i, j + 1)) {
                    *nextX = i;
                    *nextY = j + 1;
                    return;
                }
            }
        }
    }
    *nextX = -1;
}
void moveLeft(int mat[N][N], int* nextX, int* nextY, int currentX, int currentY) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == currentX && j == currentY) {
                if (isSafe(i, j - 1)) {
                    *nextX = i;
                    *nextY = j - 1;
                    return;
                }
            }
        }
    }
    *nextX = -1;
}
void moveUp(int mat[N][N], int* nextX, int* nextY, int currentX, int currentY) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == currentX && j == currentY) {
                if (isSafe(i - 1, j)) {
                    *nextX = i - 1;
                    *nextY = j;
                    return;
                }
            }
        }
    }
    *nextX = -1;
}
void moveDown(int mat[N][N], int* nextX, int* nextY, int currentX, int currentY) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == currentX && j == currentY) {
                if (isSafe(i + 1, j)) {
                    *nextX = i + 1;
                    *nextY = j;
                    return;
                }
            }
        }
    }
    *nextX = -1;
}
void solve(int initial[N][N], int blankX, int blankY) {
    struct Node* queue[30000];
    int queueCount = 0;
    struct Node* root = newNode(initial, blankX, blankY, blankX, blankY, 0, NULL);
    root->cost = calculateCost(initial);
    queue[queueCount++] = root;

    while (queueCount > 0) {
        int minIndex = 0;
        for (int i = 1; i < queueCount; i++) {
            if ((queue[i]->cost + queue[i]->level) < (queue[minIndex]->cost + queue[minIndex]->level)) {
                minIndex = i;
            }
        }
        struct Node* current = queue[minIndex];
        for (int i = minIndex; i < queueCount - 1; i++) {
            queue[i] = queue[i + 1];
        }
        queueCount--;
        if (current->cost == 0) {
            printf("SOLUTION TRAIL (ALL STEPS SHOWN):\n");
            int stepCounter = 0;
            printPath(current, &stepCounter);
            return;
        }
        int nextX, nextY;
        moveRight(current->matrix, &nextX, &nextY, current->x, current->y);
        if (nextX != -1) {
            struct Node* child = newNode(current->matrix, current->x, current->y, nextX, nextY, current->level + 1, current);
            child->cost = calculateCost(child->matrix);
            queue[queueCount++] = child;
        }
        moveLeft(current->matrix, &nextX, &nextY, current->x, current->y);
        if (nextX != -1) {
            struct Node* child = newNode(current->matrix, current->x, current->y, nextX, nextY, current->level + 1, current);
            child->cost = calculateCost(child->matrix);
            queue[queueCount++] = child;
        }
        moveUp(current->matrix, &nextX, &nextY, current->x, current->y);
        if (nextX != -1) {
            struct Node* child = newNode(current->matrix, current->x, current->y, nextX, nextY, current->level + 1, current);
            child->cost = calculateCost(child->matrix);
            queue[queueCount++] = child;
        }
        moveDown(current->matrix, &nextX, &nextY, current->x, current->y);
        if (nextX != -1) {
            struct Node* child = newNode(current->matrix, current->x, current->y, nextX, nextY, current->level + 1, current);
            child->cost = calculateCost(child->matrix);
            queue[queueCount++] = child;
        }
    }
}
int main() {
    int initial[N][N];
    int blankRow = -1, blankCol = -1;
    printf("Enter the 15-puzzle initial matrix configuration (%dx%d):\n", N, N);
    printf("(Use 0 to signify the blank tile space)\n\n");
    for (int i = 0; i < N; i++) {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);
            if (initial[i][j] == 0) {
                blankRow = i;
                blankCol = j;
            }
        }
    }
    if (blankRow == -1 || blankCol == -1) {
        printf("\nError: Invalid input. You must include '0' for the blank space.\n");
        return 1;
    }
    printf("\nYour Initial Input Matrix State:\n");
    displayTable(initial);
    printf("Calculating path... please wait...\n");
    solve(initial, blankRow, blankCol);
    return 0;
}
